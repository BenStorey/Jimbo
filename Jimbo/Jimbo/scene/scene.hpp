
#ifndef JIMBO_SCENE_SCENE_HPP
#define JIMBO_SCENE_SCENE_HPP

/////////////////////////////////////////////////////////
// Scene.h
//
// Ben Storey
//
// A scene is an abstract class that should be subclassed and have its callback methods defined
//
/////////////////////////////////////////////////////////

#include <chrono>
#include <cstdint>
#include "input/inputlistener.hpp"
#include "application/servicelocator.hpp"

namespace jimbo
{
    class InputSettings;
    enum class KeyMapping : std::uint32_t;

    class SceneManager;
    class EventManager;
    class InputManager;

    class ResourceID;

    class Scene : public InputListener
    {
    public:

        Scene() {}
        virtual ~Scene() {}

        // TODO get time since startup
        // TODO get frame delta too

        // Initialise and Shutdown allow the scene to load/unload files as necessary
        virtual bool onInitialise(std::chrono::milliseconds) = 0;
        virtual void onShutdown() = 0;

        // Pass in an update time
        virtual void onUpdate(std::chrono::milliseconds) = 0;
        virtual void onRender() = 0;

        // onNoLongerActiveScene() is called to let us know we aren't the current scene anymore
        // rename this?
        // virtual void onNoLongerActiveScene() = 0;

        // Just to help keep code clean, this could be done in init() too to be fair
        virtual void onSetupInputMaps(InputSettings& map) = 0;

        // And the callbacks. Parameter is whatever int we got mapped to (enum in practice)
        // These are the InputListener callbacks
        virtual void onKeyJustPressed   (int action) override = 0;
        virtual void onKeyJustReleased  (int action) override = 0;
        virtual void onKeyRepeat        (int action) override = 0;

        virtual void onWindowCloseEvent() override = 0;

        // I spent a lot of time trying to make this NOT public, as really no clients
        // have any business calling this. But life ends up being quite a lot simpler this way. 
        void setServiceLocator(ServiceLocator const* serviceLocator)
        {
            serviceLocator_ = serviceLocator;
        }

    protected:

        // Ends the scene from the next frame
        void endScene();
        void pushScene(std::unique_ptr<Scene> scene);
        void quitApplication();

        //std::shared_ptr<EventManager> eventManager() const { return serviceLocator_->eventManager(); }
        //std::shared_ptr<SoundManager> soundManager() const { return serviceLocator_->soundManager(); }
        //std::shared_ptr<SceneManager> sceneManager() const { return serviceLocator_->sceneManager(); }

        // Helper functions, give them a cleaner API
        void loadResource(ResourceID id);

    private:
        // Pointer to const, so we can't change the serviceLocator from here
        ServiceLocator const* serviceLocator_;
    };
}

#endif // JIMBO_SCENE_SCENE_HPP