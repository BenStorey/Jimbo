
#ifndef JIMBO_RESOURCE_RESOURCEMANAGER_HPP
#define JIMBO_RESOURCE_RESOURCEMANAGER_HPP

/////////////////////////////////////////////////////////
// resourcemanager.hpp
//
// Ben Storey
//
// ResourceManager is going to manage our resources behind the scenes, and load/unload
// them as appropriate. If everything goes to the ResourceManager for all assets then
// we get a ton of benefits (that I'll enumerate later...)
//
/////////////////////////////////////////////////////////

#include "resource/resourceid.hpp"
#include "resource/resourceloader.hpp"
#include "resource/thread/resourcethreadpool.hxx"

#include <unordered_map>
#include <memory>

namespace jimbo
{
    class ServiceLocator;

    class ResourceManager : boost::noncopyable
    {
    public:

        // We have a trivial constructor so that we can be instantiated immediately
        ResourceManager(ServiceLocator const* serviceLocator) : serviceLocator_(serviceLocator) {};

        void setThreadPoolSize(int numThreads) { numThreads_ = numThreads; }

        // Tells the ResourceManager about a resource, it's ID, and how to load it
        // ResourceManager takes ownership of these loaders
        void registerResource(ResourceID id, ResourceLoader* loader)                 { loaderMap_[id] = std::unique_ptr<ResourceLoader>(loader); }
        void registerResource(ResourceID id, std::unique_ptr<ResourceLoader> loader) { loaderMap_[id] = std::move(loader); }

        // Need to implement some form of LRU cache here I think. For now, just load it everytime it's requested
        void loadResource(ResourceID id);
        void hintLoadResource(ResourceID id) { loadResource(id); }

        // Release if we want to. Since we have no LRU cache yet, just never release them...
        // TODO - Everything for this!
        void hintReleaseResource(ResourceID id) {}
        void releaseResource(ResourceID id) {}

        // Might be useful when switching between scenes etc
        void releaseAll();

        // Log the whole universe about what's loaded and what isn't
        void logStatus();

        // reload something. Could be handy when I've swapped files out etc
        void reloadResource(ResourceID id);

        // Instantiate our thread pool
        void initialise();

        void shutdown();

        // This is where the magic shall happen
        void update();

    private:

        // Our service. Uses a pointer to const
        ServiceLocator const* serviceLocator_;

        // Loaders, so for each resource ID we can find out how to load it (from file, archive, network etc)
        std::unordered_map<ResourceID, std::unique_ptr<ResourceLoader>> loaderMap_;

        // Loaded resources
        std::unordered_map<ResourceID, std::unique_ptr<Resource>> loadedResources_;

        // Support the concept of Resource groups, as we could have dependencies between resources (an actor depends on mesh and texture say)
        // We can just 
//        std::unordered_map<ResourceID, std::vector<ResourceID>> resourceGroups_;

        // How many threads in our pool
        int numThreads_ = 1;

        // The threadpool itself
        ResourceThreadPool threadPool_;
    };

}


#endif // JIMBO_RESOURCE_RESOURCEMANAGER_HPP