
#ifndef JIMBO_AUDIO_SILENT_SILENTSOUNDMANAGER_HXX
#define JIMBO_AUDIO_SILENT_SILENTSOUNDMANAGER_HXX

/////////////////////////////////////////////////////////
// silentsoundmanager.hxx
//
// Ben Storey
//
// Implement a debug interface which doesn't make any noise .. just logs
//
/////////////////////////////////////////////////////////

#include "util/logging.hpp"
#include "audio/soundmanager.hpp"
#include "audio/silent/silentsound.hxx"

namespace jimbo
{
    class SilentSoundManager : public SoundManager
    {
    public:
        bool initialise() override final
        {
            LOG("Initialising Debug Sound");
            return true;
        }

        void shutdown() override final
        {
            LOG("Shutting down Debug Sound");
        }

        void stopAllSounds() override final
        {
            LOG("Stopping all sounds");
        }

        std::unique_ptr<jimbo::Sound> jimbo::SilentSoundManager::createSound()
        {
            return std::unique_ptr<Sound>(new SilentSound);
        }
    };
}

#endif // JIMBO_AUDIO_SILENT_SILENTSOUNDMANAGER_HXX