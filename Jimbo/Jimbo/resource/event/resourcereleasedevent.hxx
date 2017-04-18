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
        ResourceReleasedEvent(ResourceID id) : id_(id) {  }
        ResourceID getResourceID() const { return id_; }

    private:
        ResourceID id_;
    };
}

#endif // JIMBO_RESOURCE_EVENT_RELEASEDEVENT_HXX