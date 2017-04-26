
#ifndef JIMBO_RESOURCE_RESOURCELOG_HXX
#define JIMBO_RESOURCE_RESOURCELOG_HXX

/////////////////////////////////////////////////////////
// event.hxx
//
// Ben Storey
//
// Subscribes and logs events
//
/////////////////////////////////////////////////////////

#include "log/logging.hpp"
#include "event/eventhandler.hpp"
#include "resource/event/resourceloadedevent.hxx"
#include "resource/event/resourcereleasedevent.hxx"

namespace jimbo
{
    namespace log
    {
        class EventLog : public EventHandler<EventLog>
        {
        public:
            EventLog()
            {
                addEventHandler<ResourceLoadedEvent>(&EventLog::HandleResourceLoadedEvent);
                addEventHandler<ResourceReleasedEvent>(&EventLog::HandleResourceReleasedEvent);
            }

            void HandleResourceLoadedEvent(const ResourceLoadedEvent& e)
            {
                std::string logMessage = ("A resource was loaded [") + e.resourceID().str() + "] with size in bytes " + std::to_string(e.sizeInBytes());
                LOG(logMessage);
            }

            void HandleResourceReleasedEvent(const ResourceReleasedEvent& e)
            {
                std::string logMessage = ("A resource was freed [") + e.getResourceID().str() + "] with size in bytes " + std::to_string(e.getBytesFreed());
                LOG(logMessage);
            }

        };
    }
}

#endif // JIMBO_RESOURCE_RESOURCELOG_HXX