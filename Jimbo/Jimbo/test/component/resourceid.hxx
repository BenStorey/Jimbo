
#ifndef JIMBO_TEST_COMPONENT_RESOURCEID_HXX
#define JIMBO_TEST_COMPONENT_RESOURCEID_HXX

///////////////////////////////////////////////////////////////////////////////////////
// resourceid.hxx
//
// Ben Storey
//
// Tests that resource ID's are calculated appropriately
//
///////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include "resource/resourceid.hpp"

namespace jimbo
{
    namespace test
    {

        class TestResourceID
        {
        public:

            bool testEquality()
            {
                ResourceID theId = RID("one");
                ResourceID theId2 = RID("one");
                return theId == theId2;
            }

            bool testConstexpr()
            {
#ifndef _DEBUG
                constexpr std::uint32_t staticId = RID("value");
                static_assert(staticId == 510789971, "IDs are not being calculated constexpr");
#endif
                return true;
            }

        };

    }
}

#endif // JIMBO_TEST_COMPONENT_RESOURCEID_HXX