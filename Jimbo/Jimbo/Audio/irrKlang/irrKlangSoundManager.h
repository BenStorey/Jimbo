#pragma once

/////////////////////////////////////////////////////////
// irrKlangSoundManager.h
//
// Ben Storey
//
// Implement the interface using irrKlang (which is not free for commercial use!)
//
/////////////////////////////////////////////////////////

#include <irrKlang.h>
#include "audio/soundmanager.h"

namespace Jimbo
{
    class irrKlangSoundManager : public SoundManager
    {
    public:
        bool initialise() override;
        void shutdown() override;
        void stopAllSounds() override;

        std::unique_ptr<Sound> createSound() override;

    private:
        irrklang::ISoundEngine* engine_;
    };
}