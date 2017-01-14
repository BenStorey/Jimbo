#pragma once

/////////////////////////////////////////////////////////
// DebugSoundManager.h
//
// Ben Storey
//
// This is like a stub manager for sounds. It just logs when sounds should play and does nothing else. 
//
/////////////////////////////////////////////////////////

#include "SoundManager.h"
#include "../../Core/Logging.h"

namespace Jimbo
{
	class DebugSoundManager : public SoundManager
	{
		bool initialise()		override { LOG("Initialising Debug Sound Manager, no audio will actually play!"); return true; }
		void playMusic(Music&)	override { LOG("Playing some music"); }
		void playSound(Sound&)	override { LOG("Playing a sound"); }
	};
}