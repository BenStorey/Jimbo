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
#include "application/servicelocator.hpp"
#include "application/config.hpp"
#include "resource/event/resourceloadedevent.hxx"
#include "resource/event/resourcereleasedevent.hxx"
#include "event/eventmanager.hpp"
#include "log/logging.hpp"

jimbo::ResourceManager::ResourceManager(ServiceLocator const * serviceLocator) : serviceLocator_(serviceLocator)
{
    numThreads_ = serviceLocator_->config()->getResourceThreadPoolSize();
}

// Delegates the load to the threadpool
void jimbo::ResourceManager::loadResource(ResourceID id)
{
    // If we can't find a loader for it then log and do nothing
    // In production builds this should get optimised away
    if (loaderMap_.find(id) == loaderMap_.end())
    {
        LOG_ERROR("No loader available for resource [" + id.str() + "]");
        return;
    }

    threadPool_.loadResource(loaderMap_[id].get(), id);
}

void jimbo::ResourceManager::initialise()
{
    threadPool_.initialise(numThreads_);
}

void jimbo::ResourceManager::shutdown()
{
    threadPool_.shutdown();
}

void jimbo::ResourceManager::update()
{
    std::unique_ptr<Resource> result;

    // Check whether anything has been loaded. If we have something new
    // then put that into our map of loaded resources
    while (result = threadPool_.getLoadedResource())
    {
        ResourceID id = result->resourceID();
        int size = result->sizeInBytes();
        loadedResources_[result->resourceID()] = std::move(result);

        serviceLocator_->eventManager()->raiseEvent(new ResourceLoadedEvent(id, size));
    }
}
