
#ifndef JIMBO_AUDIO_SOUNDMANAGER_HPP
#define JIMBO_AUDIO_SOUNDMANAGER_HPP

/////////////////////////////////////////////////////////
// soundManager.hpp
//
// Ben Storey
//
// An interface for different sound implementations (irrKlang, cAudio etc)
//
/////////////////////////////////////////////////////////

#include <string>
#include <memory>
#include <vector>
#include <boost/noncopyable.hpp>
#include "audio/jukebox.hpp"
#include "resource/resourceid.hpp"

namespace jimbo
{
    class Sound;
    
    class SoundManager : boost::noncopyable
    {
    public:
        virtual bool initialise() = 0;
        virtual void shutdown() = 0;

        virtual void stopAllSounds() = 0;

        // TODO - This will no longer be overriden, as in here we need to track the resources
        // as and when they come available. Then the subclass should only implement the minimum

        virtual std::unique_ptr<Sound> createSound() = 0;

    private:

        // A list of resource IDs that we are waiting to load. Once they become available
        // we can properly swap in/out the sound resource
        std::vector<ResourceID> pendingResourceLoads_;

        // We own the jukebox too, for playing music tracks
        std::unique_ptr<Jukebox> jukebox;
    };
}

#endif // JIMBO_AUDIO_SOUNDMANAGER_HPP