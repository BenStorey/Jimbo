
#ifndef JIMBO_RESOURCE_DATA_MEMORYMAPPED_HPP
#define JIMBO_RESOURCE_DATA_MEMORYMAPPED_HPP

/////////////////////////////////////////////////////////
// memorymapped.hpp
//
// Ben Storey
//
// A resource that has its data loaded into a memory map
//
/////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>
#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>

#include "resource/resourceid.hpp"
#include "resource/resource.hpp"
#include "util/buffer.hxx"

namespace jimbo
{
    class ResourceMemoryMapped : public Resource
    {
    public:

        ResourceMemoryMapped(ResourceID id) : Resource(id) {}

        // Takes the boost memory mapped pointers
        ResourceMemoryMapped(ResourceID id, const char* p, int size) : Resource(id), p_(p), size_(size) {}

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
            return size_; // *sizeof(unsigned char);
        }

        bool isAvailable() const
        {
            return size_ > 0;
        }

    private:

        // Point to data
        const char* p_ = nullptr;

        // Size
        int size_ = 0;
    };

}


#endif // JIMBO_RESOURCE_DATA_MEMORYMAPPED_HPP