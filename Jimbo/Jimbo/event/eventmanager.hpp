
#ifndef JIMBO_EVENT_EVENTMANAGER_HPP
#define JIMBO_EVENT_EVENTMANAGER_HPP

///////////////////////////////////////////////////////////////////////////////////////
// eventmanager.hpp
//
// Ben Storey
//
// An Event Manager stores all pending events and dispatches them. Normally this would run
// after each frame so that the world can update based on them
//
///////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <functional>
#include <algorithm>
#include <memory>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "event/event.hpp"

namespace jimbo
{

    class EventManager : boost::noncopyable
    {
        // For now the EventManager keeps full ownership by using std::unique_ptr. It could also be very reasonable here
        // to use shared pointers, so that the client can maintain their own reference to fired events if they choose to, without
        // them getting deleted from under them. 
        using EventPtr = std::unique_ptr<EventBase>;

        // For those questionning using a vector here, watch this video! https://www.youtube.com/watch?v=LrVi9LHP8Bk
        using EventQueue = std::vector<EventPtr>;

    private:
        // Events can trigger other events, which could be bad if we are busy dispatching one of them
        // Therefor we use two queues, and when we are processing one we use the other
        EventQueue firstQueue_;
        EventQueue secondQueue_;
        EventQueue* queueInUse_;
        EventQueue* queueNotInUse_;

        // A separate queue we clear after each frame, so all "send immediate" events get cleared
        // I don't delete immediately as I'm concerned users could still accidentally reference them in the current frame
        EventQueue dispatchedEvents_;

    public:

        EventManager() : firstQueue_(), secondQueue_() { queueInUse_ = &firstQueue_; queueNotInUse_ = &secondQueue_; }
        ~EventManager() {}

        int numberEventsInQueue() { return queueInUse_->size(); }

        // Capture into smart pointer and move into the queue so we also transfer ownership. 
        void raiseEvent(EventBase* ev)
        {
            queueInUse_->emplace_back(EventPtr(ev));
        }

        // We take ownership of these with a scoped ptr. As soon as the events have been dispatched, it will be
        // destroyed as it goes out of scope
        void immediateDispatch(EventBase* ev)
        {
            ev->dispatchEvent();
            dispatchedEvents_.emplace_back(EventPtr(ev));
        }

        // Not only dispatch, also delete the pointer afterwards!
        void dispatchEvents()
        {
            // We need to switch the pointers now so that we call dispatch event on the queue not in use!
            std::swap(queueInUse_, queueNotInUse_);

            std::for_each(queueNotInUse_->cbegin(), queueNotInUse_->cend(), [](const auto& it) { it->dispatchEvent(); });

            // Clearing the list should also call the smart pointers to clear up after themselves. No deletions necessary. 
            queueNotInUse_->clear();

            // Clear the ones that have been dispatched already too, should now be safe
            dispatchedEvents_.clear();
        }
    };

}

#endif // JIMBO_EVENT_EVENTMANAGER_HPP