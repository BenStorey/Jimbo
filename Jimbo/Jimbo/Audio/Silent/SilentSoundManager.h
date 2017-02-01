#pragma once

/////////////////////////////////////////////////////////
// DebugSoundManager.h
//
// Ben Storey
//
// Implement a debug interface which doesn't make any noise .. just logs
//
/////////////////////////////////////////////////////////

#include "audio/soundmanager.h"
#include "audio/silent/silentsound.h"
#include "util/logging.h"

namespace jimbo
{
    class SilentSoundManager : public SoundManager
    {
    public:
        bool initialise() override
        {
            LOG("Initialising Debug Sound");
            return true;
        }

        void shutdown() override
        {
            LOG("Shutting down Debug Sound");
        }

        void stopAllSounds() override
        {
            LOG("Stopping all sounds");
        }

        std::unique_ptr<jimbo::Sound> jimbo::SilentSoundManager::createSound()
        {
            return std::unique_ptr<Sound>(new SilentSound);
        }
    };
}