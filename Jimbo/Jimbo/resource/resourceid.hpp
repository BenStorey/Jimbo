
#ifndef JIMBO_RESOURCE_RESOURCEID_HPP
#define JIMBO_RESOURCE_RESOURCEID_HPP

/////////////////////////////////////////////////////////
// resourceid.hpp
//
// Ben Storey
//
// Split this into it's own file since the implementation can be slightly interesting. Essentially when in debug mode,
// we want to recognise resources by a single integer ID, since that's fast for comparisons and checks/sorting etc.
// But we don't want to identify them via ID in code, it's much nicer to use strings for identification wherever possible.
// Using constexpr we can do the translation at compile time rather than runtime, which makes everyone happy
// (this might need to be reconsidered if I give a scripting interface later, but let's see...)
//
// It being typed also ensures we can't pass integers directly, it's always converted strings
//
/////////////////////////////////////////////////////////

#include <string>

// If we are in Debug mode, build from the string so we can keep it. Won't be constexpr
#ifdef _DEBUG
#define RID(x) x
#else
#define RID(x) ResourceID::generateId(x)
#endif

#include <cstdint>
#include "util/stringhash.hxx"

namespace jimbo
{
    
    class ResourceID
    {
    public:

        // If Debug, then keep the resource string around. Could be useful to see in the debugger
#ifdef _DEBUG

        std::string resourceString;

        ResourceID(const char* c) : resourceString(c)
        {
            id_ = generateId(c);
        }

        std::string str() const
        {
            return resourceString;
        }
#else
        // Maybe we don't need the production one
        std::string str() const
        {
            return std::to_string(id_);
        }

#endif

        // We use this in the public hash function, so no harm in providing an accessor
        std::uint32_t toInt() const { return id_; }

        // Regular interface
        static constexpr std::uint32_t generateId(const char* id) { return StringHash::compileTimeJenkinsStringHash(id); }
        ResourceID(std::uint32_t id) : id_(id) {}

        bool ResourceID::operator==(const ResourceID& other) const { return id_ == other.id_; }
        bool ResourceID::operator!=(const ResourceID& other) const { return !(*this == other); }

    private:
        std::uint32_t id_;

    };

}

// A hash function, so that we can have a ResourceID within an unordered_map. It's super simple, it's literally just the id...
namespace std
{
    template<>
    struct hash<jimbo::ResourceID>
    {
        size_t operator() (const jimbo::ResourceID& id) const
        {
            return id.toInt();
        }
    };
}


#endif // JIMBO_RESOURCE_RESOURCEID_HPP