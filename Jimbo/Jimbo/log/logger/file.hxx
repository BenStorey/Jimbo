
#ifndef JIMBO_LOG_FILE_HXX
#define JIMBO_LOG_FILE_HXX

/////////////////////////////////////////////////////////
// file.hxx
//
// Ben Storey
//
// Logger to write to an external file
//
/////////////////////////////////////////////////////////

#include <date/date.h>
#include <fstream>
#include <experimental\filesystem>
#include "log/logger.hpp"

namespace jimbo
{
    namespace log
    {

        class FileLogger : public Logger
        {
        public:

            FileLogger(std::string path) : path_(path) {}

            void logMessage(LogMessage message) override
            {
                std::experimental::filesystem::path p(message.filename);
                std::string toLog = date::format("%F - %T", message.time) + " - " + message.message + " (" + std::string(p.filename().string()) + ":" + std::to_string(message.linenumber) + ")\n";

                std::ofstream file;
                
                file.open(message.filename, std::ios::out | std::ios::app);
                if (file.fail())
                {
                    // Nothing we can really do here, we don't want to throw an exception and crash just because we can't write to a file
                    return;
                }

                file << toLog << std::endl;
            }

        private:
            std::string path_;
        };

    }
}

#endif // JIMBO_LOG_FILE_HXX