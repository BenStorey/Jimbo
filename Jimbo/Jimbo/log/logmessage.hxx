#ifndef JIMBO_LOG_LOGMESSAGE_HXX
#define JIMBO_LOG_LOGMESSAGE_HXX

/////////////////////////////////////////////////////////
// loggmessage.hxx
//
// Ben Storey
//
// Definition of a message
//
/////////////////////////////////////////////////////////

#include <chrono>
#include <string>

namespace jimbo
{
    namespace log
    {
        enum class LogLevel : unsigned int
        {
            Debug,
            Warning,
            Error
        };

        struct LogMessage
        {
            LogLevel level;
            std::chrono::system_clock::time_point time;
            std::string message;
            std::string filename;
            int linenumber;
        };
    }
}

#endif // JIMBO_LOG_LOGMESSAGE_HXX