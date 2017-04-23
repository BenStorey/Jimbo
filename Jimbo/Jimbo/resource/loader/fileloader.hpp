
#ifndef JIMBO_RESOURCE_FILELOADER_HPP
#define JIMBO_RESOURCE_FILELOADER_HPP

/////////////////////////////////////////////////////////
// fileloader.hpp
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

    namespace resourceloader
    {
        class FileLoader : public ResourceLoader
        {
        public:

            FileLoader(std::string path) : path_(path) {}

            std::unique_ptr<Resource> load(ResourceID id) override;

            std::string getPath() const { return path_; }

        private:

            std::string path_;
        };
    }
}

#endif // JIMBO_RESOURCE_FILELOADER_HPP