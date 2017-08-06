
#ifndef JIMBO_RESOURCE_THREAD_RESOURCETHREADPOOL_HPP
#define JIMBO_RESOURCE_THREAD_RESOURCETHREADPOOL_HPP

/////////////////////////////////////////////////////////
// resourcethreadpool.hxx
//
// Ben Storey
//
// We have a specific thread pool for loading resources. This class essentially
// wraps around our ThreadPool class but gives a nice interface for our ResourceManager
// Then our manager class need only focus on what should/shouldn't be loaded
// without any code describing how that happens
//
/////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>
#include <memory>
#include "resource/thread/threadpool.hxx"
#include "resource/thread/threadsafequeue.hxx"
#include "resource/resource.hpp"
#include "resource/resourcedatasource.hpp"

namespace jimbo
{
    class ResourceID;
    class ResourceDataSource;
    class ResourceFactory;

    class ResourceThreadPool : public ThreadPool
    {
    public:

        void loadResource(ResourceFactory*, ResourceDataSource*, ResourceID);
        std::unique_ptr<Resource> getLoadedResource();
        void updateResource(Resource*);

    private:

        ThreadSafeQueue<std::unique_ptr<Resource>> queue_;

    };
}

#endif // JIMBO_RESOURCE_THREAD_RESOURCETHREADPOOL_HPP