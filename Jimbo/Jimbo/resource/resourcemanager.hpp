
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
#include "resource/resourcedatasource.hpp"
#include "resource/resourcefactory.hxx"
#include "resource/thread/resourcethreadpool.hxx"

#include <unordered_map>
#include <memory>

namespace jimbo
{
    class ServiceLocator;

    class ResourceManager : boost::noncopyable
    {
    public:

        ResourceManager(ServiceLocator const* serviceLocator);

        void setThreadPoolSize(int numThreads) { numThreads_ = numThreads; }

        // We only want to have one copy of these factories, since they only create an object and return it anyway
        // They should be super small so we could just have a new one each time? Size wise is probably no different .. but what about the interface..
        int registerResourceFactory(ResourceFactory* factory) { int id = factories_.size(); factories_.push_back(std::unique_ptr<ResourceFactory>(factory)); return id; }

        // Tells the ResourceManager about a resource, it's ID, and how to load it
        // ResourceManager takes ownership of these loaders
        void registerResource(ResourceID id, int ResourceFactoryID, ResourceDataSource* loader) { loaderMap_[id] = std::make_pair<>(ResourceFactoryID, std::unique_ptr<ResourceDataSource>(loader)); }
        void registerResource(ResourceID id, int ResourceFactoryID, std::unique_ptr<ResourceDataSource> loader) { loaderMap_[id] = std::make_pair<>(ResourceFactoryID, std::move(loader)); }

        // Need to implement some form of LRU cache here I think. For now, just load it everytime it's requested
        // This can be called over and over in the acse of streamable resources
        void loadResource(ResourceID id);

        // Update isn't a re-read, it signals to the Resource it should do work in the background thread
        // For streamable resources this would likely involve reading more of the data into memory etc
        void updateResource(ResourceID id);

        // Tells us to release a resource. This will fire an event immediately so the rest of the world knows
        // not to try to use the resource anymore
        void releaseResource(ResourceID id);

        // Might be useful when switching between scenes etc
        void releaseAll();

        // Log the whole universe about what's loaded and what isn't
        void logStatus();

        // Essentially replaces the old Resource with a new one, helpful when reading from files etc
        // If a streamable resource is being read it will essentially reset it back to the beginning of the input stream
        void reloadResource(ResourceID id);

        // Instantiate our thread pool
        void initialise();

        void shutdown();

        // This is where the magic shall happen
        void update();

    private:

        // Our service. Uses a pointer to const
        ServiceLocator const* serviceLocator_;

        // A vector of instantiators, we give each an ID which is really just it's position in the vector
        // This lets us then store a pair of instantiators/loaders that are required for each
        std::vector<std::unique_ptr<ResourceFactory>> factories_;

        // Loaders, so for each resource ID we can find out how to load it (from file, archive, network etc)
        std::unordered_map<ResourceID, std::pair<int, std::unique_ptr<ResourceDataSource>>> loaderMap_;

        // We need a map to the constructed resources. These resources are not definitely loaded,
        // and in the case of streamable resources that doesn't really even make sense anyway..
        std::unordered_map<ResourceID, std::unique_ptr<Resource>> resourceMap_;

        // How many threads in our pool
        int numThreads_;

        // The threadpool itself
        ResourceThreadPool threadPool_;
    };

}


#endif // JIMBO_RESOURCE_RESOURCEMANAGER_HPP