#pragma once

/////////////////////////////////////////////////////////
// SilentSound.h
//
// Ben Storey
//
// This is really just used for debugging
//
/////////////////////////////////////////////////////////

#include "../Sound.h"
#include "../../Core/Logging.h"

namespace Jimbo
{
	class SilentSound : public Sound
	{
	public:
		SilentSound() {  };

		bool loadFromFile(const std::string& file) override 
		{
			std::string str = "loading " + file; LOG(str); return true;
		}

		void release() override					{ LOG("SilentSound::release()"); }

		void play() override					{ LOG("SilentSound::play()"); }
		void playLoop() override				{ LOG("SilentSound::playLoop()"); }
		void stop() override					{ LOG("SilentSound::stop()"); }

		void setPaused(bool) override			{ LOG("SilentSound::setPaused()"); }
		bool isPaused() const override			{ LOG("SilentSound::isPaused()"); return true; }
		bool isPlaying() const override			{ LOG("SilentSound::isPlaying()"); return true; }

		void setVolume(float volume) override	{ LOG("SilentSound::setVolume()"); }
		float getVolume() const override		{ LOG("SilentSound::getVolume()"); return 1.0f; }
	};
}