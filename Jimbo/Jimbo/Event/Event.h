#pragma once

///////////////////////////////////////////////////////////////////////////////////////
// Event.h
//
// Ben Storey
//
// Events are fired and received by registered callbacks, which can be really helpful. 
// Events are user-defined, and all Event objects must inherit from Event<T>
// where T is the name of the class itself. 
//
///////////////////////////////////////////////////////////////////////////////////////

#include <list>
#include <functional>
#include "EventHandler.h"

namespace Jimbo
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
	template<class T> using CallbackList = std::list< std::pair<EventHandlerBasePtr, CallbackFn<T> >>;

	template <class T>
	class Event : public EventBase
	{
	public:
		
		static void AddHandler(EventHandlerBasePtr handler, CallbackFn<T> fn)
		{
			handlers.emplace_back(std::make_pair(handler, fn));
		}

		static void RemoveHandler(EventHandlerBasePtr handler)
		{
			handlers.remove_if([&handler](auto i) {return i.first == handler; });
		}

		virtual void dispatchEvent()
		{
			std::for_each(handlers.cbegin(), handlers.cend(), [this](const auto& it) {
				(it.second) (*(static_cast<T*>(this)));
			});
		}
		
	private:
		static CallbackList<T> handlers;
	};

	// Static handlers need to be defined
	template <class T> CallbackList<T> Event<T>::handlers;
}