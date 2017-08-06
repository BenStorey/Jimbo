
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

    class Config;

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
    class ResourceDataSource;
    class ResourceFactory;

    class Application : boost::noncopyable
    {

    public:

        // Default config file location to look for if default is not provided
        const std::string DEFAULT_CONFIG_PATH = "config.toml";

        Application();
        Application(Config* config);
        ~Application();

        void run();
        
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

        void registerResource(ResourceID id, int ResourceFactoryID, ResourceDataSource* loader);
        
        int soundResource() { return SOUND_RESOURCE; }

    private:

        void initialise();
        void setupWindow();

        // On startup ownership will be transferred to the scene manager
        std::unique_ptr<Scene> startupScene_;
        
        // Our service locator contains pointers to the above manager classes. The raw
        // get pointer can then be passed around to others that need access to it. 
        std::unique_ptr<ServiceLocator> serviceLocator_;

        bool initialised_;

        int SOUND_RESOURCE;
    };
}

#endif // JIMBO_APPLICATION_HPP