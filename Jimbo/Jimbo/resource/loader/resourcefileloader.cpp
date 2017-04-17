
/////////////////////////////////////////////////////////
// resourcefileloader.cpp
//
// Ben Storey
//
// A loader that loads resources from files on disk
//
/////////////////////////////////////////////////////////

#include "resource/loader/resourcefileloader.hpp"
#include "resource/resource.hpp"
#include "resource/resourceid.hpp"

#include <iterator>
#include <fstream>

// Test
#include "util/logging.hpp"

using namespace jimbo;


std::unique_ptr<Resource> ResourceFileLoader::load(ResourceID id)
{
    std::ifstream file(path_, std::ios::binary);
    Buffer buf;
    buf.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    return std::unique_ptr<Resource>(new Resource(id, std::move(buf)));
}
