#pragma once

/////////////////////////////////////////////////////////
// irrKlangSound.h
//
// Ben Storey
//
// irrKlang's implementation of a sound
//
/////////////////////////////////////////////////////////

#include "audio/sound.h"
#include "audio/irrklang/irrklangsoundmanager.h"

namespace Jimbo
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