
#ifndef JIMBO_TEST_TESTEVENTS_HPP
#define JIMBO_TEST_TESTEVENTS_HPP

///////////////////////////////////////////////////////////////////////////////////////
// TestEvents.h
//
// Ben Storey
//
// A simpler Test class that fires some events and handles with some logging. 
//
///////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include "event/event.hpp"
#include "event/eventManager.hpp"
#include "util/logging.hpp"

namespace jimbo
{
    class TestEvents : public EventHandler<TestEvents>
    {
        class TestEvent : public jimbo::Event<TestEvent>
        {
        public:
            TestEvent(std::string m, int num) : m_(m), n_(num) { LOG("TestEvent created with " + m); }
            virtual ~TestEvent()                               { LOG("~TestEvent destructor with message " + m_); }

            const std::string& getMessage() const { return m_; }
            int getNumber() const { return n_; }

        private:
            std::string m_;
            int n_;
        };

    public:

        TestEvents()
        {
            removeEventHandler<TestEvent>();
            addEventHandler<TestEvent>(&TestEvents::HandleEvent);
        }

        void doTest()
        {
            EventManager mg;

            mg.raiseEvent(new TestEvent("TEST", 1));
            mg.raiseEvent(new TestEvent("ANOTHER", 2));
            mg.dispatchEvents();

            removeEventHandler<TestEvent>();

            mg.raiseEvent(new TestEvent("AFTER REMOVAL", 3));
            mg.raiseEvent(new TestEvent("STILL AFTER REMOVAL", 4));
            mg.dispatchEvents();

            addEventHandler<TestEvent>(&TestEvents::HandleEvent);

            mg.raiseEvent(new TestEvent("WE ARE BACK", 5));
            mg.raiseEvent(new TestEvent("HOPEFULLY", 6));
            mg.dispatchEvents();

            mg.immediateDispatch(new TestEvent("Test Immediate Dispatch", 10));
        }

        void HandleEvent(const TestEvent& theEvent)
        {
            Log::d("Handling theEvent [" + theEvent.getMessage() + ", " + std::to_string(theEvent.getNumber()) + "]\n");
        }
    };
}

#endif // JIMBO_TEST_TESTEVENTS_HPP