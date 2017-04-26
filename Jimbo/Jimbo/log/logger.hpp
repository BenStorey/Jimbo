#ifndef JIMBO_LOG_LOGGER_HPP
#define JIMBO_LOG_LOGGER_HPP

/////////////////////////////////////////////////////////
// logger.hpp
//
// Ben Storey
//
// Base class for logger implementations. It abstracts away the "level" logic
// so an implementation only needs to worry about how to log a given message 
//
/////////////////////////////////////////////////////////

#include <chrono>
#include "log/logmessage.hxx"

namespace jimbo
{
    namespace log
    {

        class Logger
        {
        public:

            Logger() { minimumLogLevel_ = LogLevel::Debug; }
            virtual ~Logger() {}
        
            void setMinimumLogLevel(LogLevel level) { minimumLogLevel_ = level; }
            LogLevel getMinimumLogLevel() const { return minimumLogLevel_; }

            // Only this function should be overriden
            virtual void logMessage(LogMessage message) = 0;

        private:

            LogLevel minimumLogLevel_;

        };
    }
}

#endif // JIMBO_LOG_LOGGER_HPP