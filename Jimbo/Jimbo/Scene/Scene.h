#pragma once

/////////////////////////////////////////////////////////
// Scene.h
//
// Ben Storey
//
// A scene is an abstract class that should be subclassed and have its callback methods defined
//
/////////////////////////////////////////////////////////

#include <chrono>
#include "../Input/KeyMapping.h"
#include "../Input/InputSettings.h"
#include "../Input/InputListener.h"
#include "../Event/EventManager.h"
#include "../Audio/SoundManager.h"
#include "SceneManager.h"

namespace Jimbo
{
    // Circular dependency, so forward declaration
    class SceneManager;

    class Scene : public InputListener
    {
    public:

        virtual ~Scene() {}

        // Initialise and Shutdown allow the scene to load/unload files as necessary
        virtual bool onInitialise(std::chrono::milliseconds) = 0;
        virtual void onShutdown() = 0;

        // Pass in an update time
        virtual void onUpdate(std::chrono::milliseconds) = 0;
        virtual void onRender() = 0;

        // onLoseFocus() is called to let us know we aren't the current scene anymore
        virtual void onLoseFocus() = 0;

        // Just to help keep code clean, this could be done in init() too to be fair
        virtual void onSetupInputMaps(InputSettings& map) = 0;

        // And the callbacks. Parameter is whatever int we got mapped to (enum in practice)
        // These are the InputListener callbacks
        virtual void onKeyJustPressed   (int action) override = 0;
        virtual void onKeyJustReleased  (int action) override = 0;
        virtual void onKeyRepeat        (int action) override = 0;

        virtual void onWindowCloseEvent() override = 0;

    protected:

        // Ends the scene from the next frame
        void endScene()              { sceneManager_->popScene(); }
        void pushScene(Scene* scene) { sceneManager_->pushScene(scene); }
        void quitApplication()       { sceneManager_->quit(); }

        EventManager* eventManager() const { return eventManager_; }
        SoundManager* soundManager() const { return soundManager_; }
        SceneManager* sceneManager() const { return sceneManager_; }

    private:
        EventManager* eventManager_;
        SoundManager* soundManager_;
        SceneManager* sceneManager_;

        // I like being able to call eventManager() or soundManager() as an API without them being singletons, which means
        // each scene needs to be able to find them from somewhere. The SceneManager can set these up, but unfortunately
        // that means they need access to Scene's private data. Hence the friend declaration..
        friend class SceneManager;
        void injectDependencies(SceneManager* sc, EventManager* ev, SoundManager* so) { sceneManager_ = sc; eventManager_ = ev, soundManager_ = so; }
    };
}