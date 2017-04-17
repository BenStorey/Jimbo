#ifndef JIMBO_RESOURCE_THREAD_THREADSAFEQUEUE_HXX
#define JIMBO_RESOURCE_THREAD_THREADSAFEQUEUE_HXX

/////////////////////////////////////////////////////////
// threadsafequeue.hxx
//
// Ben Storey
//
// To pass data between our resource manager and the running threads, we need
// a thread safe queue for appending our results onto. We could potentially
// use a boost lockfree queue instead, but that has requirements around T having trivial constructors
//
/////////////////////////////////////////////////////////

#include <mutex>
#include <queue>

namespace jimbo
{

    template <class T>
    class ThreadSafeQueue
    {
    public:

        void push(T& t)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            queue_.push(std::move(t));
        }

        // So we can't return the value directly, since one thread could enter front() or pop() after
        // another thread has taken the lock. That could cause the same task to be returned twice. 
        bool pop(T & v)
        {
            std::lock_guard<std::mutex> lock(mutex_);
            if (queue_.empty()) return false;

            v = std::move(queue_.front());
            queue_.pop();

            return true;
        }

        bool empty() const
        {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.empty();
        }

        int size() const
        {
            std::lock_guard<std::mutex> lock(mutex_);
            return queue_.size();
        }

    private:
        std::queue<T> queue_;
        std::mutex mutex_;
    };
}

#endif // JIMBO_RESOURCE_THREAD_THREADSAFEQUEUE_HXX