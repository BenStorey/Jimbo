
#ifndef JIMBO_CONFIG_HPP
#define JIMBO_CONFIG_HPP

/////////////////////////////////////////////////////////
// config.hpp
//
// Ben Storey
//
// Jimbo supports configs to be supplied in TOML format
// Everything should have a default value where possible
//
/////////////////////////////////////////////////////////

#include <string>
#include <glm/common.hpp>
#include <boost/optional/optional.hpp>
#include <boost/noncopyable.hpp>

namespace jimbo
{

    class Config : boost::noncopyable
    {
    public:
        
        ///////////////////////
        // Available options //
        ///////////////////////

        enum class AudioEngine { IRRKLANG, SILENT };

        //////////////////////////////////////////////
        // Construct from file, or use default data //
        //////////////////////////////////////////////

        Config() {}
        Config(std::string path) : path_(path) 
        { 
            reload();
        }

        void loadFromFile(std::string path)
        {
            path_ = path;
            reload();
        }

        // This is where our work is done parsing the TOML file
        void reload();
        

        ////////////////////////////
        // All available settings //
        ////////////////////////////

        void setFullScreen(bool fullScreen) { fullScreen_ = fullScreen; }
        bool isFullScreen() const { return fullScreen_; }

        void setWindowSize(int x, int y) { windowSize_ = glm::vec2(x, y); }
        void setWindowSize(glm::vec2 v) { windowSize_ = v; }
        glm::vec2 getWindowSize() const { return windowSize_; }

        void setWindowName(std::string name) { windowName_ = name; }
        std::string getWindowName() const { return windowName_; }

        void setAudioEngine(AudioEngine engine) { audioEngine_ = engine; }
        AudioEngine getAudioEngine() const { return audioEngine_; }

        void setFrameRateCap(int fps) { fps_ = fps; }
        boost::optional<int> getFrameRateCap() const { return fps_; }

        void setResourceThreadPoolSize(int numThreads) { resourceThreadPoolSize_ = numThreads; }
        int getResourceThreadPoolSize() const { return resourceThreadPoolSize_; }

        // Resources too!!


    private:

        std::string path_;

        // Variables that can be configured, all should have default values!
        bool fullScreen_ = false;
        glm::vec2 windowSize_ = glm::vec2(800,600);
        std::string windowName_ = "Jimbo Engine";
        AudioEngine audioEngine_ = AudioEngine::IRRKLANG;
        boost::optional<int> fps_;
        int resourceThreadPoolSize_ = 4;
    };
}

#endif // JIMBO_CONFIG_HPP