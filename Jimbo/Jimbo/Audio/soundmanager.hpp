
#ifndef JIMBO_AUDIO_SOUNDMANAGER_HPP
#define JIMBO_AUDIO_SOUNDMANAGER_HPP

/////////////////////////////////////////////////////////
// SoundManager.h
//
// Ben Storey
//
// An interface for different sound implementations (irrKlang, cAudio etc)
//
/////////////////////////////////////////////////////////

#include <string>
#include <memory>
#include <boost/noncopyable.hpp>

namespace jimbo
{
    class Sound;

    class SoundManager : boost::noncopyable
    {
    public:
        virtual bool initialise() = 0;
        virtual void shutdown() = 0;

        virtual void stopAllSounds() = 0;

        virtual std::unique_ptr<Sound> createSound() = 0;
    };
}

#endif // JIMBO_AUDIO_SOUNDMANAGER_HPP