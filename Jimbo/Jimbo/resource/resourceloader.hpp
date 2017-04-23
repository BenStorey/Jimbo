
#ifndef JIMBO_RESOURCE_RESOURCELOADER_HPP
#define JIMBO_RESOURCE_RESOURCELOADER_HPP

/////////////////////////////////////////////////////////
// resourceloader.hpp
//
// Ben Storey
//
// We have an abstract ResourceLoader that lets us load data
// from any number of sources without the manager needing to know
// all about them. For example load from file, or an archive, or over a network..
//
/////////////////////////////////////////////////////////

#include <memory>

namespace jimbo
{
    class Resource;
    class ResourceID;

    class ResourceLoader
    {
    public:
        virtual std::unique_ptr<Resource> load(ResourceID) = 0;
    };
}

#endif // JIMBO_RESOURCE_RESOURCELOADER_HPP