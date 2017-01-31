#pragma once

/////////////////////////////////////////////////////////
// DebugSoundManager.h
//
// Ben Storey
//
// Implement a debug interface which doesn't make any noise .. just logs
//
/////////////////////////////////////////////////////////

#include "../SoundManager.h"
#include "SilentSound.h"
#include "../../Core/Logging.h"

namespace Jimbo
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

        std::unique_ptr<Jimbo::Sound> Jimbo::SilentSoundManager::createSound()
        {
            return std::unique_ptr<Sound>(new SilentSound);
        }
    };
}