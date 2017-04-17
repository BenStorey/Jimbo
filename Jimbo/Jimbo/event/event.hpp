
#ifndef JIMBO_EVENT_EVENT_HPP
#define JIMBO_EVENT_EVENT_HPP

///////////////////////////////////////////////////////////////////////////////////////
// event.hpp
//
// Ben Storey
//
// Events are fired and received by registered callbacks, which can be really helpful. 
// Events are user-defined, and all Event objects must inherit from Event<T>
// where T is the name of the class itself. 
//
///////////////////////////////////////////////////////////////////////////////////////

#include <vector>
#include <functional>
#include <boost/range/algorithm_ext/erase.hpp>
#include "event/eventhandler.hpp"

namespace jimbo
{
    // Base class that the EventManager stores pointers to
    class EventBase
    {
    public:
        virtual void dispatchEvent() = 0;
        virtual ~EventBase() { }
    };

    // Defines to make code a little clearer and so we can easily change the signatures if needbe in one place
    using EventHandlerBasePtr = EventHandlerBase*;
    template<class T> using CallbackFn   = std::function<void(const T&)>;
    template<class T> using CallbackVec  = std::vector< std::pair<EventHandlerBasePtr, CallbackFn<T> >>;

    template <class T>
    class Event : public EventBase
    {
    public:
        
        static void AddHandler(EventHandlerBasePtr handler, CallbackFn<T> fn)
        {
            // If it's already in the vector, we don't need to add it again
            auto it = std::find_if(handlers.cbegin(), handlers.cend(), [&handler](auto i) {return i.first == handler; });

            if (it == handlers.cend())
                handlers.emplace_back(std::make_pair(handler, fn));
        }

        static void RemoveHandler(EventHandlerBasePtr handler)
        {
            boost::remove_erase_if(handlers, [&handler](auto i) {return i.first == handler; });
        }

        virtual void dispatchEvent()
        {
            std::for_each(handlers.cbegin(), handlers.cend(), [this](const auto& it) {
                (it.second) (*(static_cast<T*>(this)));
            });
        }
        
    private:
        static CallbackVec<T> handlers;
    };

    // Static handlers need to be defined
    template <class T> CallbackVec<T> Event<T>::handlers;
}

#endif // JIMBO_EVENT_EVENT_HPP