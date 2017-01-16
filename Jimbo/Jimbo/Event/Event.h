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

	using EventHandlerBasePtr = EventHandlerBase*;

	template <class T>
	class Event : public EventBase
	{
	private:

		typedef std::function<void(const T&)> CallbackFn;
		static std::list< std::pair<EventHandlerBasePtr, CallbackFn > > handlers;

	public:

		static void AddHandler(EventHandlerBasePtr handler, CallbackFn fn)
		{
			handlers.emplace_back(std::make_pair(handler, fn));
		}

		static void RemoveHandler(EventHandlerBasePtr handler)
		{
			handlers.remove_if([&handler] (auto i) {return i.first == handler; });
		}

		virtual void dispatchEvent()
		{
			std::for_each(handlers.begin(), handlers.end(), [this](auto it) { 
				 (it.second) (*(static_cast<T*>(this))); 
			});
		}

	};

	// Static handlers need to be defined
	template <class T>
	std::list< std::pair<EventHandlerBasePtr, std::function<void(const T&)> > > Event<T>::handlers;
}