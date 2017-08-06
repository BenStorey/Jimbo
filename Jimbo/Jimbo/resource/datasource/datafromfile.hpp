
#ifndef JIMBO_RESOURCE_DATAFROMFILE_HPP
#define JIMBO_RESOURCE_DATAFROMFILE_HPP

/////////////////////////////////////////////////////////
// datafromfile.hpp
//
// Ben Storey
//
// A loader that loads resources from files on disk
//
/////////////////////////////////////////////////////////

#include "resource/resourcedatasource.hpp"
#include <string>
#include <istream>

namespace jimbo
{
    class Resource;
    class ResourceID;

    class DataFromFile : public ResourceDataSource
    {
    public:

        DataFromFile(std::string path) : path_(path) {}

        virtual std::unique_ptr<std::istream> toStream(ResourceID) override;

        std::string getPath() const { return path_; }

    private:

        std::string path_;
    };    
}

#endif // JIMBO_RESOURCE_DATAFROMFILE_HPP