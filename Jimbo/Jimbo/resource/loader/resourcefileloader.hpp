
#ifndef JIMBO_RESOURCE_RESOURCEFILELOADER_HPP
#define JIMBO_RESOURCE_RESOURCEFILELOADER_HPP

/////////////////////////////////////////////////////////
// resourcefileloader.hpp
//
// Ben Storey
//
// A loader that loads resources from files on disk
//
/////////////////////////////////////////////////////////

#include "resource/resourceloader.hpp"
#include <string>

namespace jimbo
{
    class Resource;
    class ResourceID;

    class ResourceFileLoader : public ResourceLoader
    {
    public:

        ResourceFileLoader(std::string path) : path_(path) {}

        std::unique_ptr<Resource> load(ResourceID id) override;

        std::string getPath() const { return path_; }

    private:

        std::string path_;
    };

}

#endif // JIMBO_RESOURCE_RESOURCEFILELOADER_HPP