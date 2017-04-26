
#ifndef JIMBO_LOG_CONSOLE_HXX
#define JIMBO_LOG_CONSOLE_HXX

/////////////////////////////////////////////////////////
// console.hxx
//
// Ben Storey
//
// Log to console (in Linux or Debug window in VS)
//
/////////////////////////////////////////////////////////

#include <date/date.h>
#include <string>
#include <experimental\filesystem>
#include "log/logger.hpp"

// Need this for OutputDebugString
#ifdef _WIN32
    #include <Windows.h>
#else
    #include <iostream>
#endif

namespace jimbo
{
    namespace log
    {

        class ConsoleLogger : public Logger
        {
        public:
            
            void logMessage(LogMessage message) override
            {
                std::experimental::filesystem::path p(message.filename);
                std::string toPrint = date::format("%T", message.time) + " - " + message.message + " (" + std::string(p.filename().string()) + ":" + std::to_string(message.linenumber) + ")\n";

                #ifdef _WIN32
                    OutputDebugString(toPrint.c_str());
                #else
                    std::cout << toPrint;
                #endif
            }

        };
    }
}

#endif // JIMBO_LOG_CONSOLE_HXX