
#ifndef JIMBO_RESOURCE_PASSTHROUGH_HPP
#define JIMBO_RESOURCE_PASSTHROUGH_HPP

/////////////////////////////////////////////////////////
// passthrough.hpp
//
// Ben Storey
//
// This is a little bit hacky and a workaround. We don't want to do the loading/streaming
// ourselves if we are using irrKlang (or other libraries that take ownership of streaming). 
// In which case we give a "PassThrough" datasource which only passes the filepath to irrKlang
//
/////////////////////////////////////////////////////////

#include "resource/resourcedatasource.hpp"
#include <string>
#include <istream>

namespace jimbo
{
    class Resource;
    class ResourceID;

    class PassThrough : public ResourceDataSource
    {
    public:

        PassThrough(std::string path) : path_(path) {}
        
        virtual std::unique_ptr<std::istream> toStream(ResourceID) override;

        std::string getPath() const { return path_; }

    private:

        std::string path_;
    };
}

#endif // JIMBO_RESOURCE_PASSTHROUGH_HPP