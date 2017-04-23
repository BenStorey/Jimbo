
#ifndef JIMBO_TEST_COMPONENT_PROXY_HXX
#define JIMBO_TEST_COMPONENT_PROXY_HXX

///////////////////////////////////////////////////////////////////////////////////////
// proxy.hxx
//
// Ben Storey
//
// Tests for the proxy class
//
///////////////////////////////////////////////////////////////////////////////////////

#include "resource/proxy.hpp"
#include <string>

namespace jimbo
{
    namespace test
    {

        class TestProxy
        {
        public:

            Proxy<std::string> returnsProxyToString()
            {
                // memory leak I know..
                std::string* x = new std::string("testttt");
                auto i = std::make_pair(1.0f, 2.0f);

                //return make_proxy<std::string>(x);
                //return make_proxy(new std::string("returnedValue"));
                return Proxy<std::string>(x);
            }

            bool testProxyChain()
            {
                std::string test = std::string("test");

                Proxy<std::string> proxyOne(&test);
                Proxy<Proxy<std::string>> proxyTwo(&proxyOne);

                // Second should also work
                proxyOne->clear();
                proxyOne->append("after proxy one");
                proxyTwo->clear();
                proxyTwo->append("after proxy two");

                return test == "after proxy two";
            }

            bool testProxyPointer()
            {
                std::string test = "test";
                std::string* stringPtr = &test;
                Proxy<std::string*> proxyPtr(&stringPtr);
                proxyPtr->clear();
                proxyPtr->append("finished");

                return test == "finished";
            }

            bool testProxyHelper()
            {
                std::string test = "test";

                auto p = make_proxy(test);

                p->clear();

                auto p2 = make_proxy(p);
                p2->clear();
                p2->append("Success");

                return test == "Success";
            }

            bool testProxyToConst()
            {
                const std::string constString("const");
                auto cproxy = make_proxy(constString);
                auto result = cproxy->length();
                return true;
            }

        };

    }
}

#endif // JIMBO_TEST_TESTPROXY_HPP