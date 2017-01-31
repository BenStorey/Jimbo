#pragma once

/////////////////////////////////////////////////////////
// irrKlangSound.cpp
//
// Ben Storey
//
// irrKlang's implementation of a sound
//
/////////////////////////////////////////////////////////

#include "irrKlangSound.h"

Jimbo::irrKlangSound::~irrKlangSound()
{
    release();
}

bool Jimbo::irrKlangSound::loadFromFile(const std::string & file)
{
	source_ = engine_->addSoundSourceFromFile(file.c_str());

	// source lifetime is controlled by us. I'm going to grab them here so that these stay available and get dropped() 
	// on the release() call. Otherwise load/release may not have the expected behaviour
	if (source_) source_->grab();

	return source_ != nullptr;
}

void Jimbo::irrKlangSound::release()
{
	if (sound_)
	{
		sound_->drop();
		sound_ = nullptr;
	}

	if (source_)
	{
		source_->drop();
		source_ = nullptr;
	}
}

void Jimbo::irrKlangSound::play()
{
	sound_ = engine_->play2D(source_, false);
}

void Jimbo::irrKlangSound::stop()
{
	if (sound_)
		sound_->stop();
}

void Jimbo::irrKlangSound::playLoop()
{
	if (source_)
		sound_ = engine_->play2D(source_, true);
}

void Jimbo::irrKlangSound::setPaused(bool paused)
{
	if(sound_)
		sound_->setIsPaused(paused);
}

bool Jimbo::irrKlangSound::isPaused() const
{
	if (!sound_) return false;
	return sound_->getIsPaused();
}

bool Jimbo::irrKlangSound::isPlaying() const
{
	return engine_->isCurrentlyPlaying(source_);
}

void Jimbo::irrKlangSound::setVolume(float volume)
{
	if (sound_)
		sound_->setVolume(volume);
}

float Jimbo::irrKlangSound::getVolume() const
{
	if (!sound_) return 1;
	return sound_->getVolume();
}
