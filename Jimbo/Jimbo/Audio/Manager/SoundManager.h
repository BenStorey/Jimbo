#pragma once

/////////////////////////////////////////////////////////
// SoundManager.h
//
// Ben Storey
//
// We can implement the playback of sounds with different libraries, so SoundManager is more of an interface.
//
/////////////////////////////////////////////////////////

#include "../Sound.h"
#include "../Music.h"

namespace Jimbo
{
	class SoundManager
	{
	public:
		virtual ~SoundManager() {}

		virtual bool initialise() = 0;
		
		// Take a reference to the sound/music, passing in nullptr should not be valid
		virtual void playSound(Sound&) = 0;
		virtual void playMusic(Music&) = 0;
	};
}