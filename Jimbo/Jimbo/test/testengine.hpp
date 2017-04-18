#ifndef JIMBO_TEST_TESTENGINE_HPP
#define JIMBO_TEST_TESTENGINE_HPP

///////////////////////////////////////////////////////////////////////////////////////
// testengine.hpp
//
// Ben Storey
//
// A single place to run all tests and have the result displayed
//
///////////////////////////////////////////////////////////////////////////////////////

#include <map>
#include <string>
#include <boost/format.hpp>
#include "util/logging.hpp"

// Include everything test related
#include "test/component/event.hxx"
#include "test/component/proxy.hxx"
#include "test/component/resourceid.hxx"
#include "test/component/resourceloader.hxx"
#include "test/testscene.hxx"

namespace jimbo
{
    namespace test
    {
        class TestEngine
        {
        public:

            void executeAllTests()
            {
                TestProxy       testProxy;
                TestEvents      testEvents;
                TestResourceID  testResourceID;

                testResultMap["proxy/testProxyChain"]        = testProxy.testProxyChain();
                testResultMap["proxy/testProxyPointer"]      = testProxy.testProxyPointer();
                testResultMap["proxy/testProxyHelper"]       = testProxy.testProxyHelper();
                testResultMap["proxy/testProxyToConst"]      = testProxy.testProxyToConst();

                testResultMap["event/testSubscribe"]         = testEvents.testSubscribe();
                testResultMap["event/testRemoveHandler"]     = testEvents.testRemoveHandler();
                testResultMap["event/testImmediateDispatch"] = testEvents.testImmediateDispatch();
                testResultMap["event/testMultipleSubscribe"] = testEvents.testMultipleSubscribe();

                testResultMap["resourceID/testEquality"]     = testResourceID.testEquality();
                testResultMap["resourceID/testConstexpr"]    = testResourceID.testConstexpr();

            }

            void logTestResults()
            {
                std::string toLog = "\nTest Results:\n\n***************\n\n";

                int numTests = 0;
                int numTestsPassed = 0;

                for (auto it = testResultMap.cbegin(); it != testResultMap.cend(); ++it)
                {
                    toLog += (boost::format("%-35s %-10s\n") % it->first % passFail(it->second)).str();

                    numTests++;
                    if (it->second) numTestsPassed++;
                }

                toLog += "\nTest Results:\n\n***************\n\n";
                toLog += "Of " + std::to_string(numTests) + " Tests, " + std::to_string(numTestsPassed) + " Tests Succeeded\n\n***************\n\n";

                Log::d(toLog);
            }

        private:

            std::map<std::string, bool> testResultMap;

            std::string passFail(bool r)
            {
                if (r) return "Pass";
                return "Fail";
            }

        };
    }
}

#endif // JIMBO_TEST_TESTENGINE_HPP