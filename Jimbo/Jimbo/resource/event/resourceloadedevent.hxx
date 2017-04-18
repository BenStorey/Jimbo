#ifndef JIMBO_RESOURCE_EVENT_LOADEDEVENT_HXX
#define JIMBO_RESOURCE_EVENT_LOADEDEVENT_HXX

///////////////////////////////////////////////////////////////////////////////////////
// resouceloadedevent.hxx
//
// Ben Storey
//
// Fire an event whenever we've loaded a resource, and give the details of what has been loaded
// Other managers waiting for data can then subscribe and swap out resources as required
//
///////////////////////////////////////////////////////////////////////////////////////

#include "event/event.hpp"
#include "resource/resourceid.hpp"

namespace jimbo
{
    class ResourceLoadedEvent : public Event<ResourceLoadedEvent>
    {
    public:
        ResourceLoadedEvent(ResourceID id) : id_(id) {  }
        ResourceID getResourceID() const { return id_; }

    private:
        ResourceID id_;
    };
}

#endif // JIMBO_RESOURCE_EVENT_LOADEDEVENT_HXX