
/////////////////////////////////////////////////////////
// resourcefileloader.cpp
//
// Ben Storey
//
// A loader that loads resources from files on disk
//
/////////////////////////////////////////////////////////

#include "resource/loader/fileloader.hpp"
#include "resource/resource.hpp"
#include "resource/resourceid.hpp"

#include <iterator>
#include <fstream>

using namespace jimbo;
using namespace jimbo::resourceloader;


std::unique_ptr<Resource> FileLoader::load(ResourceID id)
{
    std::ifstream file(path_, std::ios::binary);
    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    return std::unique_ptr<Resource>(new Resource(id, std::move(buf)));
}
