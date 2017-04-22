
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
        virtual ~Resource() {}

        // TODO - Interface should probably always be a stream!!!!
        // Then for non streamable media just stream 100% the data every time

        // should return to the front of the memory location probably, not the vec..
        //const Buffer& data() const
        //{
        //   return buffer_;
        //}

        void release();
        int sizeInBytes() const;
        bool isAvailable() const;
        ResourceID resourceID() const { return id_; }

    protected:

        
        // Remember the resourceID we are referencing. Since these resources will get loaded within
        // another thread and passed back, it's helpful to embed the id so we can see what the pool
        // has loaded without having to track individual threads
        ResourceID id_;
    };

}


#endif // JIMBO_RESOURCE_RESOURCE_HPP