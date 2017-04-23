#ifndef JIMBO_AUDIO_JUKEBOX_HPP
#define JIMBO_AUDIO_JUKEBOX_HPP

/////////////////////////////////////////////////////////
// jukebox.hpp
//
// Ben Storey
//
// To seamlessly handle music playlists. 
//
/////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>
#include <vector>
#include <chrono>

namespace jimbo
{
    class ResourceID;

    class Jukebox : boost::noncopyable
    {
    public:

        // service locator?
        Jukebox() {}
    
        // This will also remove what was already there..
        void setPlaylist(std::vector<ResourceID> ids) { ids_ = ids; stop(); }

        void play();
        void pause();
        void stop();

        // Support going quiet gradually between music tracks
        // In AAA world we'd have composed music for transitions, but we won't go quite so far ..
        void setTransitionFadeOutTime(std::chrono::milliseconds millis);
        void setTransitionFadeInTime(std::chrono::milliseconds millis);

        // Minimum time to keep playing a track before allowing another transition
        void setMinimumDurationBeforeTrackSwitch(std::chrono::milliseconds millis);

    private:

        std::vector<ResourceID> ids_;
    };
}


#endif // JIMBO_AUDIO_JUKEBOX_HPP