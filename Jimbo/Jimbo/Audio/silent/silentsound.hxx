
#ifndef JIMBO_AUDIO_SILENT_SILENTSOUND_HXX
#define JIMBO_AUDIO_SILENT_SILENTSOUND_HXX

/////////////////////////////////////////////////////////
// silentsound.hxx
//
// Ben Storey
//
// This is really just used for debugging
//
/////////////////////////////////////////////////////////

#include "audio/sound.hpp"
#include "util/logging.hpp"

namespace jimbo
{
    class SilentSound : public Sound
    {
    public:
        SilentSound() {  };

        bool loadFromFile(const std::string& file) override 
        {
            std::string str = "loading " + file; LOG(str); return true;
        }

        void release()               override       { LOG("SilentSound::release()"); }

        void play()                  override       { LOG("SilentSound::play()"); }
        void playLoop()              override       { LOG("SilentSound::playLoop()"); }
        void stop()                  override       { LOG("SilentSound::stop()"); }

        void setPaused(bool)         override       { LOG("SilentSound::setPaused()"); }
        bool isPaused()              const override { LOG("SilentSound::isPaused()"); return true; }
        bool isPlaying()             const override { LOG("SilentSound::isPlaying()"); return true; }

        void setVolume(float volume) override       { LOG("SilentSound::setVolume()"); }
        float getVolume()            const override { LOG("SilentSound::getVolume()"); return 1.0f; }
    };
}

#endif // JIMBO_AUDIO_SILENT_SILENTSOUND_HXX