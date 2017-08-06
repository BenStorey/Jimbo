
/////////////////////////////////////////////////////////
// datafromfile.cpp
//
// Ben Storey
//
// A loader that loads resources from files on disk
//
/////////////////////////////////////////////////////////

#include "resource/datasource/datafromfile.hpp"
#include "resource/resource.hpp"
#include "resource/resourceid.hpp"

#include <iterator>
#include <fstream>
#include <istream>

using namespace jimbo;

std::unique_ptr<std::istream> DataFromFile::toStream(ResourceID id)
{
    std::ifstream* file = new std::ifstream(path_, std::ios::binary);
    return std::unique_ptr<std::istream>(std::move(file));
}
