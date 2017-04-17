/////////////////////////////////////////////////////////
// resourcemanager.cpp
//
// Ben Storey
//
// ResourceManager is going to manage our resources behind the scenes, and load/unload
// them as appropriate. If everything goes to the ResourceManager for all assets then
// we get a ton of benefits (that I'll enumerate later...)
//
/////////////////////////////////////////////////////////

#include "resource/resourcemanager.hpp"
#include "util/logging.hpp"

// Delegates the load to the threadpool
void jimbo::ResourceManager::loadResource(ResourceID id)
{
    // If we can't find a loader for it then log and do nothing
    if (loaderMap_.find(id) == loaderMap_.end())
    {
        LOG("No loader available for resource: " + id.str());
        return;
    }

    threadPool_.loadResource(loaderMap_[id].get(), id);
}

void jimbo::ResourceManager::initialise()
{
    threadPool_.initialise(numThreads_);
}

void jimbo::ResourceManager::update()
{
    std::unique_ptr<Resource> result;

    // Check whether anything has been loaded. If we have something new
    // then put that into our map of loaded resources
    while (result = threadPool_.getLoadedResource())
    {
        loadedResources_[result->resourceID()] = std::move(result);
        std::string logMessage = ("A resource was loaded: ") + result->resourceID().str() + " with size in bytes " + std::to_string(result->sizeInBytes());
        LOG(logMessage);
    }

    // More magic?
}
