#pragma once

///////////////////////////////////////////////////////////////////////////////////////
// EventManager.h
//
// Ben Storey
//
// An Event Manager stores all pending events and dispatches them. Normally this would run
// after each frame so that the world can update based on them
//
///////////////////////////////////////////////////////////////////////////////////////

#include <list>
#include <functional>
#include <algorithm>
#include <memory>
#include <boost/noncopyable.hpp>
#include <boost/scoped_ptr.hpp>

#include "event/event.h"


namespace jimbo
{

    class EventManager : boost::noncopyable
    {
        // For now the EventManager keeps full ownership by using std::unique_ptr. It could also be very reasonable here
        // to use shared pointers, so that the client can maintain their own reference to fired events if they choose to, without
        // them getting deleted from under them. 
        using EventPtr = std::unique_ptr<EventBase>;

        // For now we're using a simple list for our list of pending events. 
        using EventQueue = std::list<EventPtr>;

    private:
        // Events can trigger other events, which could be bad if we are busy dispatching one of them
        // Therefor we use two queues, and when we are processing one we use the other
        EventQueue firstQueue_;
        EventQueue secondQueue_;
        EventQueue* queueInUse_;
        EventQueue* queueNotInUse_;

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
            boost::scoped_ptr<EventBase> e(ev);
            e->dispatchEvent();
        }

        // Not only dispatch, also delete the pointer afterwards!
        void dispatchEvents()
        {
            // We need to switch the pointers now so that we call dispatch event on the queue not in use!
            std::swap(queueInUse_, queueNotInUse_);

            std::for_each(queueNotInUse_->cbegin(), queueNotInUse_->cend(), [](const auto& it) { it->dispatchEvent(); });

            // Clearing the list should also call the smart pointers to clear up after themselves. No deletions necessary. 
            queueNotInUse_->clear();
        }
    };

}