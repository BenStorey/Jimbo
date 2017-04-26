#ifndef JIMBO_LOG_EXECUTIONTIME_HXX
#define JIMBO_LOG_EXECUTIONTIME_HXX

/////////////////////////////////////////////////////////
// executiontime.hxx
//
// Ben Storey
//
// Little helper if I ever want to log how long a function takes to execute
//
/////////////////////////////////////////////////////////

#include <boost/noncopyable.hpp>
#include <chrono>
#include "log/logging.hpp"

namespace jimbo
{
    namespace log
    {
        class LogExecutionTime : boost::noncopyable
        {
        public:

            LogExecutionTime() : start_(std::chrono::high_resolution_clock::now()) { }
            ~LogExecutionTime()
            {
                auto duration = std::chrono::high_resolution_clock::now() - start_;
                LOG("Block executed in " + std::to_string(std::chrono::duration_cast<std::chrono::milliseconds>(duration).count()) + " milliseconds");
            }

        private:
            std::chrono::high_resolution_clock::time_point start_;
        };
    }
}

#endif // JIMBO_LOG_EXECUTIONTIME_HXX