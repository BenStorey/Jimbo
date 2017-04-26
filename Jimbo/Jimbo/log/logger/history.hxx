#ifndef JIMBO_LOG_HISTORY_HXX
#define JIMBO_LOG_HISTORY_HXX

/////////////////////////////////////////////////////////
// history.hxx
//
// Ben Storey
//
// Maintains a list of recent log messages in a circular buffer. At some stage we may
// want to be able to actually render the log messages directly to the screen
//
/////////////////////////////////////////////////////////

#include <boost/circular_buffer.hpp>
#include "log/logger.hpp"

namespace jimbo
{
    namespace log
    {

        class LogHistory : public Logger
        {
        public:

            LogHistory(int size) : history_(size) {}
            
            virtual void logMessage(LogMessage message) override
            {
                history_.push_front(message);
            }

        private:
            boost::circular_buffer<LogMessage> history_;
        };
    }
}

#endif // JIMBO_LOG_HISTORY_HXX