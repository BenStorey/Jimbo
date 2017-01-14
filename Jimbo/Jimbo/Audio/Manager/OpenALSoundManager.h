#pragma once

/////////////////////////////////////////////////////////
// OpenALSoundManager.h
//
// Ben Storey
//
// An OpenAL implementation
//
/////////////////////////////////////////////////////////

#include "SoundManager.h"

// AL implementation
#include <AL/al.h>
#include <AL/alc.h>

#include <string>

namespace Jimbo
{
	class OpenALSoundManager : public SoundManager
	{
	public:
		bool initialise() override;

		virtual void playSound(Sound&) override;
		virtual void playMusic(Music&) override;

	private:
		void			  debugPrintAudioDevices(const ALCchar* devices);
		const std::string getOpenALErrorString(int);
		inline void		  checkOpenALError(const char* statement, const char* filename, int line);

		ALuint source_;
		ALuint buffer_;
	};
}