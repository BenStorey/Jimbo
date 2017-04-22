#ifndef JIMBO_RESOURCE_MEMORYMAPLOADER_HPP
#define JIMBO_RESOURCE_MEMORYMAPLOADER_HPP

/////////////////////////////////////////////////////////
// memorymaploader.hpp
//
// Ben Storey
//
// A loader that loads resources from disk directly into memory, should be faster
//
/////////////////////////////////////////////////////////

#include "resource/resourceloader.hpp"
#include <string>

namespace jimbo
{
    class Resource;
    class ResourceID;

    namespace resource
    {
        class MemoryMapLoader : public Loader
        {
        public:

            MemoryMapLoader(std::string path) : path_(path) {}

            std::unique_ptr<Resource> load(ResourceID id) override;

            std::string getPath() const { return path_; }

        private:

            std::string path_;
        };
    }
}

#endif // JIMBO_RESOURCE_MEMORYMAPLOADER_HPP