#ifndef JIMBO_RESOURCE_EVENT_RELEASEDEVENT_HXX
#define JIMBO_RESOURCE_EVENT_RELEASEDEVENT_HXX

///////////////////////////////////////////////////////////////////////////////////////
// resoucereleasedevent.hxx
//
// Ben Storey
//
// Fire an event whenever we've released a resource too. 
//
///////////////////////////////////////////////////////////////////////////////////////

#include "event/event.hpp"
#include "resource/resourceid.hpp"

namespace jimbo
{
    class ResourceReleasedEvent : public Event<ResourceReleasedEvent>
    {
    public:
        ResourceReleasedEvent(ResourceID id, int bytesFreed) : id_(id), bytesFreed_(bytesFreed) {  }
        ResourceID getResourceID() const { return id_; }
        int getBytesFreed() const { return bytesFreed_; }

    private:
        ResourceID id_;
        int bytesFreed_;
    };
}

#endif // JIMBO_RESOURCE_EVENT_RELEASEDEVENT_HXX