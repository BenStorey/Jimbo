
#ifndef JIMBO_LOG_LOGGING_HPP
#define JIMBO_LOG_LOGGING_HPP

/////////////////////////////////////////////////////////
// logging.hpp
//
// Ben Storey
//
// We want LOG / LOG_ERROR / LOG_DEBUG / LOG_WARN etc to work everywhere
// This means we essentially want a single static place to send queries into
// This file is that static object with the macro definitions for access
//
/////////////////////////////////////////////////////////

#include "log/logengine.hxx"

// Can eventually change this out to std::source_location, but it doesn't exist yet :(
#define LOG(x) jimbo::log::log(jimbo::log::LogLevel::Debug, x, __FILE__, __LINE__ );

// By level
#define LOG_DEBUG(x) jimbo::log::log(jimbo::log::LogLevel::Debug, x, __FILE__, __LINE__ );
#define LOG_WARN (x) jimbo::log::log(jimbo::log::LogLevel::Warning, x, __FILE__, __LINE__ );
#define LOG_ERROR(x) jimbo::log::log(jimbo::log::LogLevel::Error, x, __FILE__, __LINE__ );

namespace jimbo
{
    namespace log
    {
        // Provide global static accessors
        static LogEngine _globalLog;

        static void log(LogLevel level, const std::string& message, const char* filename, int linenumber)
        {
            _globalLog.log(level, message, filename, linenumber);
        }

        static void attachLogger(Logger* logger) { _globalLog.attachLogger(logger); }
        static void attachLogger(std::shared_ptr<Logger> logger) { _globalLog.attachLogger(logger); }

        static void detachLogger(Logger* logger) { _globalLog.attachLogger(logger); }
        static void detachLogger(std::shared_ptr<Logger> logger) { _globalLog.detachLogger(logger); }

        static bool loggingEnabled() { return _globalLog.loggingEnabled(); }
    }
}

#endif // JIMBO_LOG_LOGGING_HPP