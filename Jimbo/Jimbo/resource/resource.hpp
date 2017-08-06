
#ifndef JIMBO_RESOURCE_RESOURCE_HPP
#define JIMBO_RESOURCE_RESOURCE_HPP

/////////////////////////////////////////////////////////
// resource.hpp
//
// Ben Storey
//
// A resource is an object that can be loaded and read from an istream
// The representation for how these are stored should be determined
// by any subclasses. For resources that get streamed in/out, these may
// also require explicit synchronisation in the implementing class
//
/////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>
#include <vector>
#include "resource/resourceid.hpp"

namespace jimbo
{
    class Resource : boost::noncopyable
    {
    public:

        Resource(ResourceID id) : id_(id) { }
        virtual ~Resource() {}

        virtual void release() = 0;
        virtual int sizeInBytes() const = 0;

        // read will normally read all the data entirely. Textures etc don't make sense to load partially
        virtual void read(std::unique_ptr<std::istream> s) = 0;

        // Music etc may want to stream piece by piece. For that it should keep a reference to the istream
        // and then implement loads here as appropriate. As the name implies, it will process this call in another thread
        virtual void updateInBackgroundThread() {}
        
        // Streamable resources will typically set this to no until they've been loaded in full
        // Non-streamable resources should load everything at once, so after being read set this to yes
        virtual bool isFullyLoaded() = 0;

        ResourceID resourceID() const { return id_; }

        // To be called by the ResourceManager, implementing classes shouldn't be concerned with these...
        //void setInputStream(std::unique_ptr<std::istream> s) { stream_ = std::move(s); }
        //void releaseInputStream() { stream_ = nullptr; }
        //bool hasInputStream() const { return stream_ != nullptr; }

    protected:

        
        // Remember the resourceID we are referencing. Since these resources will get loaded within
        // another thread and passed back, it's helpful to embed the id so we can see what the pool
        // has loaded without having to track individual threads
        ResourceID id_;

        // The istream is also provided for the lifetime of the resource (at least, as long as it isn't released)
        // The resource itself needs to take ownership since it should remember the place when readBytes() is called
        //std::unique_ptr<std::istream> stream_;
    };

}


#endif // JIMBO_RESOURCE_RESOURCE_HPP