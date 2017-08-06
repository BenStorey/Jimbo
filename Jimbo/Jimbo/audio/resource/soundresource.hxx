#ifndef JIMBO_AUDIO_SOUNDRESOURCE_HXX
#define JIMBO_AUDIO_SOUNDRESOURCE_HXX

/////////////////////////////////////////////////////////
// soundresource.hxx
//
// Ben Storey
//
// Represents a sound resource. Just loading raw data into a buffer should work!
//
/////////////////////////////////////////////////////////

#include <memory>
#include "resource/resource.hpp"

namespace jimbo
{
    class SoundResource : public Resource
    {
    public:
        SoundResource(ResourceID id) : Resource(id) {}

        void release() override
        {

        }

        int sizeInBytes() const override
        {
            return 0;
        }

        // read will normally read all the data entirely. Textures etc don't make sense to load partially
        void read(std::unique_ptr<std::istream> s) override
        {
            
        }

        bool isFullyLoaded() override
        {
            return false;
        }
    };
}

#endif // JIMBO_AUDIO_SOUNDRESOURCE_HXX