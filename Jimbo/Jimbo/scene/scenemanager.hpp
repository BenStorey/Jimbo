
#ifndef JIMBO_SCENE_SCENEMANAGER_HPP
#define JIMBO_SCENE_SCENEMANAGER_HPP

/////////////////////////////////////////////////////////
// SceneManager.h
//
// Ben Storey
//
// A scene manager, to handle transitions between user defined scenes
//
/////////////////////////////////////////////////////////

#include <stack>
#include <memory>
#include <chrono>
#include <boost/noncopyable.hpp>
#include "log/logging.hpp"

#include "scene/scene.hpp"

namespace jimbo
{
    // Forward declaration for a scene, since both include each other
    class Scene;
    class ServiceLocator;

    class SceneManager : boost::noncopyable
    {
    public:

        // Use a steady clock for timing, as it won't get messed up if the system clock changes
        using Clock = std::chrono::steady_clock;

        SceneManager(ServiceLocator const* serviceLocator) : serviceLocator_(serviceLocator), gameEnding_(false), popScene_(0) {};

        bool hasActiveScene() const { return !sceneStack_.empty(); }

        void pushScene(Scene* newScene) { nextScene_ = std::unique_ptr <Scene>(newScene); }
        void pushScene(std::unique_ptr<Scene> newScene) { nextScene_ = std::move(newScene); }

        void popScene() { ++popScene_; }

        // Normally the scene manager shouldn't be visible to users, so it's fine to leave this in public I think
        // Preferable to making Application a friend in this case
        void runGameLoop();

        // Ends the whole application, called by user scenes. 
        void quit() 
        {
            LOG("Quit() called, application will close");
            gameEnding_ = true; 
        }

    private:

        void checkNextScene();
        void checkEndApplication();

        // rather than make a choice between 32 and 64 bit, rely on std::chrono::milliseconds
        std::chrono::milliseconds getElapsedTime() { auto now = Clock::now(); return std::chrono::duration_cast<std::chrono::milliseconds>(now - startTime_); }

        // I have a tingling sense that the SceneManager shouldn't really take ownership of the Scene classes themselves
        // but because it will have called shutdown() already on the last scene, I think it's probably fine. User can always recreate and push
        std::stack<std::unique_ptr<Scene>> sceneStack_;

        // The next scene, ready to initialise and put onto the stack
        std::unique_ptr<Scene> nextScene_;

        // How many scenes to pop at the end of this frame
        int popScene_;
        bool gameEnding_;

        // The start time for our game loop
        std::chrono::time_point<Clock> startTime_;

        // Our service. Uses a pointer to const
        ServiceLocator const* serviceLocator_;
    };
}

#endif // JIMBO_SCENE_SCENEMANAGER_HPP