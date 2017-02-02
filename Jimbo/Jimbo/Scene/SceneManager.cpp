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

void jimbo::SceneManager::runGameLoop()
{
    startTime_ = Clock::now();
    
    checkNextScene();

    while (hasActiveScene())
    {
        checkNextScene();

        auto elapsedTime = getElapsedTime();
        auto currentScene = sceneStack_.top().get();

        // Update input
        inputManager_->update();

        // Update our scene logic based on elapsed time
        currentScene->onUpdate(elapsedTime);

        // Render the world
        renderer_->startRenderFrame();
        currentScene->onRender();
        renderer_->endRenderFrame();

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
        inputManager_->removeListener(sceneStack_.top().get());

        sceneStack_.top()->onShutdown();
        sceneStack_.pop();
        --popScene_;
    }

    if (nextScene_)
    {
        nextScene_->injectDependencies(this, eventManager_, soundManager_);
        nextScene_->onInitialise(getElapsedTime());

        if (!sceneStack_.empty())
            inputManager_->removeListener(sceneStack_.top().get());

        // For now, only the topmost scene will receive input actions
        inputManager_->addListener(nextScene_.get());
        inputManager_->resetInputSettings();
        nextScene_->onSetupInputMaps(inputManager_->getInputSettingsToEdit());

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

