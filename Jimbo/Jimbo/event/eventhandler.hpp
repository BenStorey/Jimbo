
#ifndef JIMBO_EVENT_EVENTHANDLER_HPP
#define JIMBO_EVENT_EVENTHANDLER_HPP

///////////////////////////////////////////////////////////////////////////////////////
// eventhandler.hpp
//
// Ben Storey
//
// Events are handled by registered callbacks. Normally in a constructor/destructor
// you would addEventHandler() and removeEventHandler() from the event type as appropriate. 
// At the moment the assumption is that callbacks will always be made back to member functions
// To be an event handler, inherit from EventHandler<T> where T is the name of the new class
// To register for an event, call addEventHandler<EventType>(&memberFunc)
//
///////////////////////////////////////////////////////////////////////////////////////

namespace jimbo
{
    // We have a base class because we need to store a list of these pointers to call
    class EventHandlerBase
    {
    public:
        virtual ~EventHandlerBase() { }
    };

    // EventT in the template is the type of Event being subscribed to
    template <class T>
    class EventHandler : public EventHandlerBase
    {
    public:

        template <class EventT>
        void addEventHandler(void (T::*memFn)(const EventT&))
        {
            EventT::AddHandler(this, std::bind(memFn, static_cast<T*>(this), std::placeholders::_1));
        }

        template <class EventT>
        void removeEventHandler()
        {
            EventT::RemoveHandler(this);
        }
    };

}

#endif // JIMBO_EVENT_EVENTHANDLER_HPP