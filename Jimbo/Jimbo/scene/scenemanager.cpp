/////////////////////////////////////////////////////////
// SceneManager.h
//
// Ben Storey
//
// A scene manager, to handle transitions between user defined scenes
//
/////////////////////////////////////////////////////////

#include <chrono>
#include "scene/scenemanager.hpp"
#include "scene/scene.hpp"
#include "graphics/renderer.hpp"
#include "input/inputmanager.hpp"
#include "resource/resourcemanager.hpp"
#include "event/eventmanager.hpp"


void jimbo::SceneManager::runGameLoop()
{
    startTime_ = Clock::now();
    auto endFrameTime = startTime_;
    auto startFrameTime = startTime_;

    
    checkNextScene();

    while (hasActiveScene())
    {
        checkNextScene();

        auto endFrameTime = Clock::now();
        auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(endFrameTime - startFrameTime);
        auto startFrameTime = Clock::now();

        auto elapsedTime = getElapsedTime();
        auto currentScene = sceneStack_.top().get();

        // Update input
        serviceLocator_->inputManager()->update();

        // Let the resource manager handle any changes
        serviceLocator_->resourceManager()->update();

        // Update our scene logic based on elapsed time
        currentScene->onUpdate(delta);

        // Render the world
        serviceLocator_->renderer()->startRenderFrame();
        currentScene->onRender();
        serviceLocator_->renderer()->endRenderFrame();

        // Fire any events that have been handled during the frame
        serviceLocator_->eventManager()->dispatchEvents();

        // Check we haven't finished
        checkEndApplication();
    }

    // End of the program

}

// Manage our scene stack
void jimbo::SceneManager::checkNextScene()
{
    while (popScene_ > 0)
    {
        serviceLocator_->inputManager()->removeListener(sceneStack_.top().get());

        sceneStack_.top()->onShutdown();
        sceneStack_.pop();
        --popScene_;
    }

    if (nextScene_)
    {
        // We are a friend of all scenes, so we can set some handy variables for it
        nextScene_->serviceLocator_ = serviceLocator_;
        nextScene_->sceneRunTime_ = std::chrono::milliseconds(0);
        nextScene_->applicationRunTime_ = getElapsedTime();

        // Initialise it
        nextScene_->onInitialise(getElapsedTime());

        if (!sceneStack_.empty())
            serviceLocator_->inputManager()->removeListener(sceneStack_.top().get());

        // For now, only the topmost scene will receive input actions
        serviceLocator_->inputManager()->addListener(nextScene_.get());
        serviceLocator_->inputManager()->resetInputSettings();
        nextScene_->onSetupInputMaps(serviceLocator_->inputManager()->getInputSettingsToEdit());

        // Needs to be moved in, once its removed from the stack it will be destroyed
        sceneStack_.push(std::move(nextScene_));
    }
}

void jimbo::SceneManager::checkEndApplication()
{
    if (gameEnding_)
    {
        while (!sceneStack_.empty())
        {
            sceneStack_.top()->onShutdown();
            sceneStack_.pop();
        }
    }

    // Theoretically we could have another scene pending also, but it's initialise function
    // won't have been called yet. Therefore it should be safe to allow it to expire without
    // calling its onShutdown() function
}

