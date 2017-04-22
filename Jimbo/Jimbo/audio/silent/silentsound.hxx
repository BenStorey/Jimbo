
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
#include "log/logging.hpp"

namespace jimbo
{
    class SilentSound : public Sound
    {
    public:
        SilentSound() {  };

        bool loadFromFile(const std::string& file) override final
        {
            std::string str = "loading " + file; LOG(str); return true;
        }

        void release()               override final       { LOG("SilentSound::release()"); }

        void play()                  override final       { LOG("SilentSound::play()"); }
        void playLoop()              override final       { LOG("SilentSound::playLoop()"); }
        void stop()                  override final       { LOG("SilentSound::stop()"); }

        void setPaused(bool)         override final       { LOG("SilentSound::setPaused()"); }
        bool isPaused()              const override final { LOG("SilentSound::isPaused()"); return true; }
        bool isPlaying()             const override final { LOG("SilentSound::isPlaying()"); return true; }

        void setVolume(float volume) override final       { LOG("SilentSound::setVolume()"); }
        float getVolume()            const override final { LOG("SilentSound::getVolume()"); return 1.0f; }
    };
}

#endif // JIMBO_AUDIO_SILENT_SILENTSOUND_HXX