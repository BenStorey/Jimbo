
#ifndef JIMBO_RESOURCE_DATA_BUFFERED_HPP
#define JIMBO_RESOURCE_DATA_BUFFERED_HPP

/////////////////////////////////////////////////////////
// buffered.hpp
//
// Ben Storey
//
// A resource that stores the data in a vector
//
/////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>
#include "resource/resourceid.hpp"
#include "resource/resource.hpp"
#include "util/buffer.hxx"

namespace jimbo
{
    class ResourceBuffered : public Resource
    {
    public:

        ResourceBuffered(ResourceID id) : Resource(id) {}
        ResourceBuffered(ResourceID id, Buffer&& data) : Resource(id), buffer_(std::move(data)) {}

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


    private:

        // A buffer of loaded data, if available
        Buffer buffer_;
    };

}


#endif // JIMBO_RESOURCE_DATA_BUFFERED_HPP