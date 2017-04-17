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
#include "resource/resourceloader.hpp"
#include "resource/resourceid.hpp"
#include "resource/resource.hpp"
#include "util/logging.hpp"

using namespace jimbo;

// Takes the ID to load as well as the loader. We also wrap in a try/catch to ensure
// exceptions don't kill the application. 

void ResourceThreadPool::loadResource(ResourceLoader* loader, ResourceID id)
{
    // Need a local reference to pass into the lambda
    auto& queue = queue_;

    service_.post([loader, id, &queue]()
    {
        try
        {
            auto result = loader->load(id);
            queue.push(result);
        }
        catch (const std::exception &e)
        {
            std::string err = "Exception whilst loading resource " + id.str() + " [" + std::string(e.what()) + "]";
            LOG(err);
        }
    });
}

// Pops the last value into our pointer. If it returns false, then just pass
// an empty pointer back to the caller (since nothing was moved)

std::unique_ptr<Resource> jimbo::ResourceThreadPool::getLoadedResource()
{
    std::unique_ptr<Resource> resource = nullptr;

    // Pops the top value into our resource pointer
    queue_.pop(resource);
        
    // We don't need to check the return value of the above, if it returned false we are fine to
    // return our nullptr anyway
    return resource;
}

