/////////////////////////////////////////////////////////
// InputManager.cpp
//
// Ben Storey
//
/////////////////////////////////////////////////////////

#include "InputManager.h"

// Store the start time and do our callbacks
void Jimbo::InputManager::keyJustPressed(KeyMapping key, KeyModifier mod)
{
	auto action = settings_.getAction(key, mod);
	if (action)
	{
		actionStartTimes_[action.get()] = ClockType::now();
		std::for_each(listeners_.cbegin(), listeners_.cend(), [action](const auto& it) { it->onKeyJustPressed(action.get()); });
	}
}

// Clear it from the map when released and do all our callbacks
void Jimbo::InputManager::keyJustReleased(KeyMapping key, KeyModifier mod)
{
	auto action = settings_.getAction(key, mod);
	if (action)
	{
		actionStartTimes_.erase(action.get());
		std::for_each(listeners_.cbegin(), listeners_.cend(), [action](const auto& it) { it->onKeyJustReleased(action.get()); });
	}
}

// Check how long since it was pressed, and only callback if its longer than the repeat interval
void Jimbo::InputManager::keyRepeat(KeyMapping key, KeyModifier mod)
{
	auto action = settings_.getAction(key, mod);
	if (!action) return;

	auto duration = settings_.getRepeatInterval(action.get());

	// If the action isn't already there, then add it in and set the time to now
	if (actionStartTimes_.find(action.get()) == actionStartTimes_.end())
	{
		actionStartTimes_[action.get()] = ClockType::now();
	}

	auto start = actionStartTimes_[action.get()];

	// If we are after the repeat time, then we are going to execute our callbacks
	if (!duration || ClockType::now() > (start + duration.get()))
	{
		if (duration) 
			actionStartTimes_[action.get()] = start + duration.get();

		std::for_each(listeners_.cbegin(), listeners_.cend(), [action](const auto& it) { it->onKeyRepeat(action.get()); });
	}
}

void Jimbo::InputManager::windowCloseEvent()
{
	std::for_each(listeners_.cbegin(), listeners_.cend(), [](const auto& it) { it->onWindowCloseEvent(); });
}