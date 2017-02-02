
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
        bool initialise() override;
        void shutdown() override;
        void stopAllSounds() override;

        std::unique_ptr<Sound> createSound() override;

    private:
        irrklang::ISoundEngine* engine_;
    };
}

#endif // JIMBO_AUDIO_IRRKLANG_IRRKLANGSOUNDMANAGER_HXX