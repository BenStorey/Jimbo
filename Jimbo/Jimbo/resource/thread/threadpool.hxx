
#ifndef JIMBO_RESOURCE_THREAD_THREADPOOL_HPP
#define JIMBO_RESOURCE_THREAD_THREADPOOL_HPP

/////////////////////////////////////////////////////////
// threadpool.hxx
//
// Ben Storey
//
// A very simple thread pool around boost::asio. 
//
/////////////////////////////////////////////////////////

// We use boost thread instead of std::thread because it supports thread_group

#include <boost/asio.hpp>
#include <boost/thread.hpp>
#include <boost/noncopyable.hpp>
#include <memory>
#include <functional>

#include "util/logging.hpp"

namespace jimbo
{
    
    class ThreadPool : boost::noncopyable
    {
    public:

        ThreadPool(): running_(false) {}
        ~ThreadPool() { shutdown(); }

        void initialise(int numThreads)
        {
            // This work object uses its constructor to notify the io_service that work is starting..
            // If this isn't created then the run() function may not work properly
            work_.reset(new boost::asio::io_service::work(service_));

            for (int i = 0; i < numThreads; i++)
            {
                auto thread = boost::bind(&boost::asio::io_service::run, &service_);
                group_.add_thread(new boost::thread(thread));
            }

            running_ = true;
        }

        // Shuts down the pool and all threads. Any future tasks will be ignored. 
        void shutdown()
        {
            if (!running_) return;

            group_.join_all();
            service_.stop();

            running_ = false;
        }

        bool isRunning() const
        {
            return running_;
        }

        
    protected:

        // We let subclasses post tasks to the service_ directly
        boost::asio::io_service service_;

    private:

        std::unique_ptr<boost::asio::io_service::work> work_;
        boost::thread_group group_;

        bool running_;
    };
}

#endif // JIMBO_RESOURCE_THREAD_THREADPOOL_HPP