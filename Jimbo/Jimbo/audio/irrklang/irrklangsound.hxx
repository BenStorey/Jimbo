
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

        bool loadFromFile(const std::string& file) override final;
        void release() override final;

        void play() override final;
        void playLoop() override final;
        void stop() override final;

        void setPaused(bool) override final;
        bool isPaused() const override final;
        bool isPlaying() const override final;

        void setVolume(float volume) override final;
        float getVolume() const override final;

    private:
        irrklang::ISoundEngine* engine_;
        irrklang::ISoundSource* source_;
        irrklang::ISound* sound_;
    };
}

#endif // JIMBO_AUDIO_IRRKLANG_IRRKLANGSOUND_HXX