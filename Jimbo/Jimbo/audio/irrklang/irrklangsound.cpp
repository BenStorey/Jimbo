/////////////////////////////////////////////////////////
// irrKlangSound.cpp
//
// Ben Storey
//
// irrKlang's implementation of a sound
//
/////////////////////////////////////////////////////////

#include "audio/irrklang/irrklangsound.hxx"

jimbo::irrKlangSound::~irrKlangSound()
{
    release();
}

bool jimbo::irrKlangSound::loadFromFile(const std::string & file)
{
    source_ = engine_->addSoundSourceFromFile(file.c_str());

    // source lifetime is controlled by us. I'm going to grab them here so that these stay available and get dropped() 
    // on the release() call. Otherwise load/release may not have the expected behaviour
    if (source_) source_->grab();

    return source_ != nullptr;
}

void jimbo::irrKlangSound::release()
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

void jimbo::irrKlangSound::play()
{
    sound_ = engine_->play2D(source_, false);
}

void jimbo::irrKlangSound::stop()
{
    if (sound_)
        sound_->stop();
}

void jimbo::irrKlangSound::playLoop()
{
    if (source_)
        sound_ = engine_->play2D(source_, true);
}

void jimbo::irrKlangSound::setPaused(bool paused)
{
    if(sound_)
        sound_->setIsPaused(paused);
}

bool jimbo::irrKlangSound::isPaused() const
{
    if (!sound_) return false;
    return sound_->getIsPaused();
}

bool jimbo::irrKlangSound::isPlaying() const
{
    return engine_->isCurrentlyPlaying(source_);
}

void jimbo::irrKlangSound::setVolume(float volume)
{
    if (sound_)
        sound_->setVolume(volume);
}

float jimbo::irrKlangSound::getVolume() const
{
    if (!sound_) return 1;
    return sound_->getVolume();
}
