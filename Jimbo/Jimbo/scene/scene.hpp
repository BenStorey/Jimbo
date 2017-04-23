
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

#include <set>
#include <chrono>
#include <cstdint>
#include <boost/container/flat_set.hpp>

#include "input/inputlistener.hpp"
#include "application/servicelocator.hpp"

namespace jimbo
{
    class InputSettings;
    enum class KeyMapping : std::uint32_t;

    class EventBase;
    class SceneManager;
    class EventManager;
    class InputManager;

    class ResourceID;
    
    class Scene : public InputListener
    {
    private:
        
        // Note the use of a flat_set! It's basically a sorted vector. I use them instead of a set because
        // I need to be able to move a pointer out of it, but all set iterators are const so this can't be done
        // Using a sorted vector is probably faster than a regular set anyway ... (cache locality etc)
        // Actually it was benchmarked, and flat_set should beat std::set for up to 150 elements or so. Ours will likely be smaller. 
        struct TimeCompare;
        using FireEventTime = std::pair<std::chrono::milliseconds, std::unique_ptr<EventBase>>;
        //using PendingEventSet = boost::container::flat_set<FireEventTime, TimeCompare>;
        using PendingEventSet = std::set<FireEventTime, TimeCompare>;

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
        virtual void onKeyJustPressed(int action) override = 0;
        virtual void onKeyJustReleased(int action) override = 0;
        virtual void onKeyRepeat(int action) override = 0;

        virtual void onWindowCloseEvent() override = 0;

        // Should have a concept of SceneTime vs ApplicationTime or something, where 
        // SceneTime is the time passed since this scene was initialised. So if you want
        // to throw an event 2s in the future, you'd probably want it to happen during
        // sceneTime and not when the game is paused or something...
        void setSceneTime(std::chrono::nanoseconds time);

    protected:

        // Ends the scene from the next frame
        void endScene();

        // Ownership is taken away when a new scene is pushed
        void pushScene(Scene* scene);
        void pushScene(std::unique_ptr<Scene> scene);

        void quitApplication();

        // Helper functions, give them a cleaner API
        void loadResource(ResourceID id);

        // Event handling. Support raising events here with the scene time (not overall time)
        void raiseEvent(EventBase* ev);
        void raiseEvent(std::unique_ptr<EventBase> ev);
        void raiseEventDelayed(EventBase* ev, std::chrono::milliseconds delay) 
        { 
            // We hint that it will be at the end, which is more likely than it being earlier than previous events
            pendingEvents_.emplace_hint(pendingEvents_.cend(), std::make_pair(sceneRunTime_ + delay, std::unique_ptr<EventBase>(ev)));
        }

        void clearPendingEvents() { pendingEvents_.clear(); }

    private:

        // We store our own list of delayed events, so we can be ensure we delay them by sceneTime
        // Ordering by the time to fire means we don't need to look over the full list each frame
        struct TimeCompare
        {
            bool operator()(const FireEventTime &a, const FireEventTime &b)
            {
                return a.first < b.first;
            }
        };

        PendingEventSet pendingEvents_;
        /*
        void checkPendingEvents()
        {
            for (auto i = pendingEvents_.begin(); i != pendingEvents_.end(); )
            {
                if (sceneRunTime_ > i->first)
                {
                    //raiseEvent(std::move(i->second));
                    //i = pendingEvents_.erase(i);
                }
                else
                {
                    // We're a sorted container, so there must be nothing left to do...
                    break;
                }
            }
        }*/

        // I never liked friend classes so this deserves a bit of extra thought. 
        // However on each frame there is data I'd like to be made available from the scene manager,
        // and making it a friend so it doesn't pollute the client interface seems somehow cleaner

        friend SceneManager;

        ServiceLocator const* serviceLocator_;
        std::chrono::milliseconds applicationRunTime_;
        std::chrono::milliseconds sceneRunTime_;
    };
}

#endif // JIMBO_SCENE_SCENE_HPP