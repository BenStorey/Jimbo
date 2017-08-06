#ifndef JIMBO_AUDIO_SOUNDRESOURCEFACTORY_HXX
#define JIMBO_AUDIO_SOUNDRESOURCEFACTORY_HXX

/////////////////////////////////////////////////////////
// soundresourcefactory.hxx
//
// Ben Storey
//
// Instantiates sound resources
//
/////////////////////////////////////////////////////////

#include <memory>
#include "resource/resource.hpp"
#include "resource/resourceid.hpp"
#include "resource/resourcefactory.hxx"
#include "audio/resource/soundresource.hxx"

namespace jimbo
{
    class SoundResourceFactory : public ResourceFactory
    {
        std::unique_ptr<Resource> instantiate(ResourceID id) override
        {
            return std::unique_ptr<Resource>(new SoundResource(id));
        }
    };
}

#endif // JIMBO_AUDIO_SOUNDRESOURCEFACTORY_HXX