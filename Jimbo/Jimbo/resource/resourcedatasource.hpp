
#ifndef JIMBO_RESOURCE_RESOURCEDATASOURCE_HPP
#define JIMBO_RESOURCE_RESOURCEDATASOURCE_HPP

/////////////////////////////////////////////////////////
// resourcedatasource.hpp
//
// Ben Storey
//
// We have an abstract ResourceDataSource that lets us load data
// from any number of sources without the manager needing to know
// all about them. For example load from file, or an archive, or over a network..
//
/////////////////////////////////////////////////////////

#include <memory>
#include <istream>

namespace jimbo
{
    class Resource;
    class ResourceID;

    class ResourceDataSource
    {
    public:
        virtual std::unique_ptr<std::istream> toStream(ResourceID) = 0;
    };
}

#endif // JIMBO_RESOURCE_RESOURCEDATASOURCE_HPP