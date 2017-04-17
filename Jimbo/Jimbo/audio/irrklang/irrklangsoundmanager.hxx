
#ifndef JIMBO_AUDIO_IRRKLANG_IRRKLANGSOUNDMANAGER_HXX
#define JIMBO_AUDIO_IRRKLANG_IRRKLANGSOUNDMANAGER_HXX

/////////////////////////////////////////////////////////
// irrklangsoundmanager.hxx
//
// Ben Storey
//
// Implement the interface using irrKlang (which is not free for commercial use!)
//
/////////////////////////////////////////////////////////

#include <irrKlang.h>
#include "audio/soundmanager.hpp"

namespace jimbo
{
    class irrKlangSoundManager : public SoundManager
    {
    public:
        bool initialise() override final;
        void shutdown() override final;
        void stopAllSounds() override final;

        std::unique_ptr<Sound> createSound() override final;

    private:
        irrklang::ISoundEngine* engine_;
    };
}

#endif // JIMBO_AUDIO_IRRKLANG_IRRKLANGSOUNDMANAGER_HXX