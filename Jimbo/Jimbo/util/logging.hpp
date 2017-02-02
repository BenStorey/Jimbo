
#ifndef JIMBO_UTIL_LOGGING_HPP
#define JIMBO_UTIL_LOGGING_HPP

/////////////////////////////////////////////////////////
// Logging.h
//
// Ben Storey
//
// Static logging class to help debugging
//
/////////////////////////////////////////////////////////

#include <string>
#include <experimental\filesystem>

#ifdef _WIN32
    #include <Windows.h>
#endif

// Helper if you want file/line numbers
// Can eventually change this out to std::source_location, but it doesn't exist yet :(
#define LOG(x) jimbo::Log::d(x, __FILE__, __LINE__ );

namespace jimbo
{
    class Log
    {
    public:

        static void d(const std::string& s, const char* file, int lineNumber)
        {
#ifdef _DEBUG
            std::experimental::filesystem::path p(file);
            std::string toPrint = s + " (" + std::string(p.filename().string()) + ":" + std::to_string(lineNumber) + ")\n";
            d(toPrint);
#endif
        }

        static void d(const std::string& s)
        {
            #ifdef _DEBUG
                #ifdef _WIN32
            OutputDebugString(s.c_str());
                #endif
            #endif
        }
    };

}

#endif // JIMBO_UTIL_LOGGING_HPP