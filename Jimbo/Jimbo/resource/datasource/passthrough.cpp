
/////////////////////////////////////////////////////////
// passthrough.cpp
//
// Ben Storey
//
// Very simply implementation ...
//
/////////////////////////////////////////////////////////

#include "resource/datasource/passthrough.hpp"
#include "resource/resource.hpp"
#include "resource/resourceid.hpp"

#include <istream>
#include <sstream>

using namespace jimbo;

std::unique_ptr<std::istream> PassThrough::toStream(ResourceID id)
{
    std::istringstream* stream = new std::istringstream(path_);
    return std::unique_ptr<std::istream>(std::move(stream));

    /*buf = std::move(file);
    buf.
    buf << file;

    std::vector<char> buf;
    buf.assign(std::istreambuf_iterator<char>(file), std::istreambuf_iterator<char>());

    return std::unique_ptr<Resource>(new Resource(id, std::move(buf)));*/
}
