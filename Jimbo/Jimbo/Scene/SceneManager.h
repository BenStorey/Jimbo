#pragma once

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
#include "../Event/EventManager.h"
#include "../Audio/SoundManager.h"
#include "../Input/InputManager.h"
#include "../Graphics/Renderer.h"
#include "../Core/Logging.h"

namespace Jimbo
{
    // Forward declaration for a scene, since both include each other
    class Scene;

    class SceneManager : boost::noncopyable
    {
    public:

        // Use a steady clock for timing, as it won't get messed up if the system clock changes
        using Clock = std::chrono::steady_clock;

        // The reason I take pointers rather than const ref, is because I need Scene's to be able to be constructed without them being available by the user
        // as they get injected later (without needing to be deleted, since they are owned by the Application class)
        SceneManager(Renderer* r, InputManager* im, EventManager* em, SoundManager* sm) 
            : renderer_(r), inputManager_(im), eventManager_(em), soundManager_(sm), gameEnding_(false), popScene_(0) {};

        bool hasActiveScene() const { return !sceneStack_.empty(); }

        void pushScene(Scene* newScene) { nextScene_.reset(newScene); }
        void popScene()                 { ++popScene_; }

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

        // Our managers..
        InputManager* inputManager_;
        EventManager* eventManager_;
        SoundManager* soundManager_;
        Renderer*     renderer_;
    };
}