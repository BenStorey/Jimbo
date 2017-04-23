
#ifndef JIMBO_RESOURCE_RESOURCE_HPP
#define JIMBO_RESOURCE_RESOURCE_HPP

/////////////////////////////////////////////////////////
// resource.hpp
//
// Ben Storey
//
// A resource is something that is managed by our resource manager and loaded/unloaded behind the scenes
// Currently I just store the data in a vector, but I should probably consider
// just having the assets mapped directly into memory. 
//
/////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>
#include "resource/resourceid.hpp"
#include "util/buffer.hxx"

namespace jimbo
{
    class Resource : boost::noncopyable
    {
    public:

        Resource(ResourceID id) : id_(id) {}
        Resource(ResourceID id, Buffer&& data) : id_(id), buffer_(std::move(data)) {}
        virtual ~Resource() {}

        // TODO - Interface should probably always be a stream!!!!
        // Then for non streamable media just stream 100% the data every time

        // Swap trick to force the buffer to be released
        void release()
        {
            buffer_ = Buffer(0);
        }

        // should return to the front of the memory location probably, not the vec..
        //const Buffer& data() const
        //{
        //   return buffer_;
        //}

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