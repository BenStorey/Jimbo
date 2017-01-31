#pragma once

/////////////////////////////////////////////////////////
// Sound.h
//
// Ben Storey
//
// An abstraction for a sound. Different implementations can load/release these as necessary
//
/////////////////////////////////////////////////////////

#include <string>
#include <boost/noncopyable.hpp>

namespace Jimbo
{
	// A 2D Sound. Eventually I'll need to support 3D sounds also
	class Sound : boost::noncopyable
	{
	public:

		// A sound should release its resources when destroyed, so ensuring
		// its called in the destructor allows us to use unique_ptr semantics for them
        virtual ~Sound() {}

		// Loading and releasing the file from memory
		virtual bool loadFromFile(const std::string& file) = 0;
		virtual void release() = 0;

		virtual void play() = 0;
		virtual void playLoop() = 0;
		virtual void stop() = 0;
		
		virtual void setPaused(bool) = 0;
		virtual bool isPaused() const = 0;
		virtual bool isPlaying() const = 0;

		// 0 --> 1.0f
		virtual void setVolume(float volume) = 0;
		virtual float getVolume() const = 0;
	};
}