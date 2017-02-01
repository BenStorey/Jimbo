#pragma once

/////////////////////////////////////////////////////////
// InputManager.h
//
// Ben Storey
//
// Another abstraction for input libraries. For now should be simple to wrap the glfw window
//
// It holds a vector of listeners and calls all of them, although the current behaviour is for
// the sceneManager to ensure only one scene is listening at a time. This seems to simplify the
// Scene code for now since scenes can ignore input actions from all the others. Eventually
// this restriction will probably be lifted, which is why I've used a vector for now
//
/////////////////////////////////////////////////////////

#include <chrono>
#include <boost/noncopyable.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include "input/inputlistener.h"
#include "input/inputsettings.h"

namespace jimbo
{
    class InputManager : boost::noncopyable
    {
    public:
        
        virtual ~InputManager() {}

        virtual void initialise()   = 0;
        virtual void shutdown()     = 0;
        virtual void update()       = 0;

        // Manage our listeners
        void addListener(InputListener* listener)       { listeners_.push_back(listener); }
        void removeListener(InputListener* listener)    { boost::remove_erase(listeners_, listener); }
        void removeAllListeners()                       { listeners_.clear(); }

        // Set the action settings
        void resetInputSettings()               { settings_.reset(); }
        InputSettings& getInputSettingsToEdit() { return settings_; }

    protected:

        // InputManager Implementations can call these functions as appropriate, and the logic here will manage the appropriate callbacks to scenes
        void keyJustPressed  (KeyMapping key, KeyModifier mod);
        void keyJustReleased (KeyMapping key, KeyModifier mod);
        void keyRepeat       (KeyMapping key, KeyModifier mod);

        void windowCloseEvent();

    private:

        // The settings that determine how Key maps will map to actions. Set by user scenes
        InputSettings settings_;

        // To make callbacks too
        std::vector<InputListener*> listeners_;

        // We time how long states have been in the state they are in. If a repeat is called, we only send that to the listener if
        // the repeat duration time has elapsed, otherwise it's ignored. 
        using Clock = std::chrono::steady_clock;
        std::unordered_map<InputSettings::Action, Clock::time_point> actionStartTimes_;

    };
}