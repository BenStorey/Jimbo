/////////////////////////////////////////////////////////
// resourcethreadpool.cpp
//
// Ben Storey
//
// Implementation
//
/////////////////////////////////////////////////////////

#include <memory>
#include "resource/thread/resourcethreadpool.hxx"
#include "resource/resourcefactory.hxx"
#include "resource/resourcedatasource.hpp"
#include "resource/resourceid.hpp"
#include "resource/resource.hpp"
#include "log/logging.hpp"

using namespace jimbo;

// Takes the ID to load as well as the loader. We also wrap in a try/catch to ensure
// exceptions don't kill the application. 
void ResourceThreadPool::loadResource(ResourceFactory* factory, ResourceDataSource* loader, ResourceID id)
{
    // Need a local reference to pass into the lambda
    auto& queue = queue_;

    service_.post([factory, loader, id, &queue]()
    {
        try
        {
            auto result = loader->toStream(id);
            auto instance = factory->instantiate(id);
            instance->read(std::move(result));
            queue.push(instance);
        }
        catch (const std::exception &e)
        {
            std::string err = "Exception whilst loading resource " + id.str() + " [" + std::string(e.what()) + "]";
            LOG(err);
        }
    });
}

// Calls the "updateInBackgroundThread" function, which streamable resources can use
// to update as appropriate. 
void ResourceThreadPool::updateResource(Resource * resource)
{
    service_.post([resource]() 
    {
        try
        {
            resource->updateInBackgroundThread();
        }
        catch (const std::exception &e)
        {
            std::string err = "Exception whilst updating resource " + resource->resourceID().str() + " [" + std::string(e.what()) + "]";
            LOG(err);
        }
    });
}



// Pops the last value into our pointer. If it returns false, then just pass
// an empty pointer back to the caller (since nothing was moved)
std::unique_ptr<Resource> ResourceThreadPool::getLoadedResource()
{
    std::unique_ptr<Resource> resource = nullptr;

    // Pops the top value into our resource pointer
    queue_.pop(resource);
        
    // We don't need to check the return value of the above, if it returned false we are fine to
    // return our nullptr anyway
    return resource;
}
