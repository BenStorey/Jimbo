
#ifndef JIMBO_LOG_LOGENGINE_HXX
#define JIMBO_LOG_LOGENGINE_HXX

/////////////////////////////////////////////////////////
// logengine.hxx
//
// Ben Storey
//
// We could potentially want to log to different places with different log levels,
// like to the console in debug mode, or to a file for errors only. Or even to a database
// during testing!
//
// Therefore we instantiate a single log class where we can register multiple "sinks", 
// that all log messages will get sent to
// 
//
/////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>
#include <boost/range/algorithm_ext/erase.hpp>
#include <vector>
#include <memory>
#include <chrono>
#include "log/logmessage.hxx"
#include "log/logger.hpp"

namespace jimbo
{
    namespace log
    {
        class LogEngine : boost::noncopyable
        {
        public:

            void log(LogLevel level, const std::string& message, const char* filename, int linenumber)
            {
                LogMessage log;
                
                log.level = level;
                log.message = message;
                log.filename = std::string(filename);
                log.time = std::chrono::system_clock::now();
                log.linenumber = linenumber;

                std::for_each(loggers_.begin(), loggers_.end(), 
                    [&log](const auto& it) { 
                    if (log.level >= it->getMinimumLogLevel()) it->logMessage(log); });
            }

            void attachLogger(Logger* logger) { loggers_.emplace_back(std::shared_ptr<Logger>(logger)); }
            void attachLogger(std::shared_ptr<Logger> logger) { loggers_.emplace_back(logger); }
            void detachLogger(Logger* logger) { boost::remove_erase_if(loggers_, [logger](auto i) {return i.get() == logger; }); }
            void detachLogger(std::shared_ptr<Logger> logger) { boost::remove_erase_if(loggers_, [logger](auto i) {return i.get() == logger.get(); }); }

            bool loggingEnabled() const { return !loggers_.empty(); }

        private:

            // It doesn't seem unreasonable that a user would want to maintain a reference to the logger so
            // they can change the debug level, attach/re-attach it during runtime etc. Therefore we use
            // shared_ptr so we don't destroy the users logger
            std::vector<std::shared_ptr<Logger>> loggers_;
        };

    }
}


#endif // JIMBO_LOG_LOGENGINE_HXX