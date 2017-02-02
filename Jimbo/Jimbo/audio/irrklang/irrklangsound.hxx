
#ifndef JIMBO_AUDIO_IRRKLANG_IRRKLANGSOUND_HXX
#define JIMBO_AUDIO_IRRKLANG_IRRKLANGSOUND_HXX

/////////////////////////////////////////////////////////
// irrKlangSound.hxx
//
// Ben Storey
//
// irrKlang's implementation of a sound
//
/////////////////////////////////////////////////////////

#include "audio/sound.hpp"
#include "audio/irrklang/irrklangsoundmanager.hxx"

namespace jimbo
{
    class irrKlangSound : public Sound
    {
    public:
        irrKlangSound(irrklang::ISoundEngine* engine) : engine_(engine), source_(nullptr), sound_(nullptr) { };
        ~irrKlangSound();

        bool loadFromFile(const std::string& file) override;
        void release() override;

        void play() override;
        void playLoop() override;
        void stop() override;

        void setPaused(bool) override;
        bool isPaused() const override;
        bool isPlaying() const override;

        void setVolume(float volume) override;
        float getVolume() const override;

    private:
        irrklang::ISoundEngine* engine_;
        irrklang::ISoundSource* source_;
        irrklang::ISound* sound_;
    };
}

#endif // JIMBO_AUDIO_IRRKLANG_IRRKLANGSOUND_HXX