
#ifndef JIMBO_APPLICATION_HPP
#define JIMBO_APPLICATION_HPP

/////////////////////////////////////////////////////////
// application.hpp
//
// Ben Storey
//
// This is the entry point for running a Jimbo game. Controls the window and controls the scene management,
// and manages startup settings.
//
/////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include <memory>
#include <boost/optional/optional.hpp>
#include <boost/noncopyable.hpp>

#include "application/servicelocator.hpp"

namespace jimbo
{

    class Scene;
    class ServiceLocator;

    // services
    class SoundManager;
    class InputManager;
    class EventManager;
    class SceneManager;
    class ResourceManager;
    class Renderer;

    // resources
    class ResourceID;
    class ResourceLoader;

    class Application : boost::noncopyable
    {

    public:

        enum class AudioEngine { IRRKLANG, SILENT };

        Application();
        ~Application();

        void run();

        // Window modes
        void setWindowName(const std::string& name) { this->windowName_ = name; };
        void setFullScreen(bool isFullScreen)       { this->fullScreen_ = isFullScreen; };
        void setWindowSize(int x, int y)            { windowSizeX_ = x; windowSizeY_ = y; }

        // Audio choices
        void setAudioEngine(AudioEngine ae)         { audioEngine_ = ae; }

        // This takes a unique pointer at the moment so that the user knows
        // they are losing ownership
        void setStartupScene(std::unique_ptr<Scene> startupScene)   
        { 
            startupScene_ = std::move(startupScene);
        }

        void setStartupScene(Scene* startupScene)
        {
            startupScene_.reset(startupScene);
        }

        // Resource related. We just pass through to the manager directly, but lets the user set these before starting the app
        void setResourceThreadPoolSize(int numThreads);
        void registerResource(ResourceID id, ResourceLoader* loader); 

        // Use optional for framerates, as you can pass an empty to turn it off
        void capFrameRate(boost::optional<int> fps) { this->fps_ = fps; }
        void capFrameRate(int fps)                  { this->fps_ = boost::make_optional(fps); }
        boost::optional<int> getFrameRate() const   { return fps_; }

    private:

        void initialise();
        void setupWindow();

        // On startup ownership will be transferred to the scene manager
        std::unique_ptr<Scene> startupScene_;

        // Use unique pointer because we want ownership of it. 
        AudioEngine audioEngine_;

        // Our service locator contains pointers to the above manager classes. The raw
        // get pointer can then be passed around to others that need access to it. 
        std::unique_ptr<ServiceLocator> serviceLocator_;

        bool initialised_;
        bool fullScreen_;
        std::string windowName_;
        boost::optional<int> fps_;

        int windowSizeX_;
        int windowSizeY_;
    };
}

#endif // JIMBO_APPLICATION_HPP