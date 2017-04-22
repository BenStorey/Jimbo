
/////////////////////////////////////////////////////////
// memorymaploader.cpp
//
// Ben Storey
//
// Map files directly into memory, should be much faster
//
/////////////////////////////////////////////////////////

#include "resource/loader/memorymaploader.hpp"
#include "resource/resource.hpp"
#include "resource/resourceid.hpp"

#include <boost/interprocess/file_mapping.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <iostream>

using namespace jimbo;
using namespace jimbo::resource;

// Maybe this implementation is better?
// https://www.eriksmistad.no/memory-mapped-files-using-the-boost-library/

std::unique_ptr<Resource> MemoryMapLoader::load(ResourceID id)
{
    boost::interprocess::file_mapping mapping (path_.c_str(), boost::interprocess::read_only);
    boost::interprocess::mapped_region mappedRegion(mapping, boost::interprocess::read_only);
    char const* const data = static_cast<char*>(mappedRegion.get_address());
    std::size_t const size = mappedRegion.get_size();

    // Loaded resource needs to do the below
    // mapping.remove(path_.c_str());

    // Probably we need two resource types for this to work. A ResourceBuffer and a ResourceRaw or something..
    

    return std::unique_ptr<Resource>(new Resource(id, std::move(buf)));
}
