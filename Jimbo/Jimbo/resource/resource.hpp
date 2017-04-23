
#ifndef JIMBO_RESOURCE_RESOURCE_HPP
#define JIMBO_RESOURCE_RESOURCE_HPP

/////////////////////////////////////////////////////////
// resource.hpp
//
// Ben Storey
//
// A resource is something that is managed by our resource manager and loaded/unloaded behind the scenes
//
// Expect this to be completely replaced as the logic for loading/releasing assets is implemented...
//
/////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>
#include <vector>
#include "resource/resourceid.hpp"

namespace jimbo
{
    class Resource : boost::noncopyable
    {
    public:

        using Buffer = std::vector<char>;

        Resource(ResourceID id) : id_(id) {}
        Resource(ResourceID id, Buffer&& data) : id_(id), buffer_(std::move(data)) {}
        virtual ~Resource() {}

        // Swap trick to force the buffer to be released
        void release()
        {
            buffer_ = Buffer(0);
        }

        int sizeInBytes() const
        {
            return buffer_.size() * sizeof(unsigned char);
        }

        bool isAvailable() const
        {
            return buffer_.size() > 0;
        }

        ResourceID resourceID() const { return id_; }

    protected:

        
        // Remember the resourceID we are referencing. Since these resources will get loaded within
        // another thread and passed back, it's helpful to embed the id so we can see what the pool
        // has loaded without having to track individual threads
        ResourceID id_;

        // A buffer of loaded data, if available
        Buffer buffer_;
    };

}


#endif // JIMBO_RESOURCE_RESOURCE_HPP