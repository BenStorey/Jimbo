
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
#include <boost/optional/optional.hpp>
#include <boost/noncopyable.hpp>

namespace jimbo
{

    class ResourceFactory;

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

        void setWindowSize(int x, int y) { windowSizeX_ = x; windowSizeY_ = y; }
        int getWindowSizeX() const { return windowSizeX_; }
        int getWindowSizeY() const { return windowSizeY_; }

        void setWindowName(std::string name) { windowName_ = name; }
        std::string getWindowName() const { return windowName_; }

        void setAudioEngine(AudioEngine engine) { audioEngine_ = engine; }
        AudioEngine getAudioEngine() const { return audioEngine_; }

        void setFrameRateCap(int fps) { fps_ = fps; }
        boost::optional<int> getFrameRateCap() const { return fps_; }

        void setResourceThreadPoolSize(int numThreads) { resourceThreadPoolSize_ = numThreads; }
        int getResourceThreadPoolSize() const { return resourceThreadPoolSize_; }

        // Resources too!! The config will determine how resources are created
        ResourceFactory* soundResource() const { return soundResource_; }
        ResourceFactory* musicResource() const { return musicResource_; }
        ResourceFactory* textureResource() const { return textureResource_; }


    private:

        std::string path_;

        // Variables that can be configured, all should have defaults
        bool fullScreen_ = false;
        int windowSizeX_ = 800;
        int windowSizeY_ = 600;
        std::string windowName_ = "Jimbo Engine";
        AudioEngine audioEngine_ = AudioEngine::IRRKLANG;
        boost::optional<int> fps_;
        int resourceThreadPoolSize_ = 4;

        // Resource factories - ownership of these gets given to the ResourceManager, so we just store raw pointers instead. 
        ResourceFactory* soundResource_;
        ResourceFactory* musicResource_;
        ResourceFactory* textureResource_;
    };
}

#endif // JIMBO_CONFIG_HPP