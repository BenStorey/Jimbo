
#ifndef JIMBO_RESOURCE_RESOURCEFACTORY_HXX
#define JIMBO_RESOURCE_RESOURCEFACTORY_HXX

/////////////////////////////////////////////////////////
// resourcefactory.hxx
//
// Ben Storey
//
// ResourceManager needs to also know how to instantiate resources. We can pass in
// a reference to an object that knows how to do it!
//
/////////////////////////////////////////////////////////

#include <memory>
#include "resource/resource.hpp"
#include "resource/resourceid.hpp"

namespace jimbo
{
    class ResourceFactory
    {
    public:
        virtual std::unique_ptr<Resource> instantiate(ResourceID) = 0;
    };
}

#endif // JIMBO_RESOURCE_RESOURCEFACTORY_HXX