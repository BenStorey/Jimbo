
#ifndef JIMBO_TEST_COMPONENT_EVENT_HPP
#define JIMBO_TEST_COMPONENT_EVENT_HPP

///////////////////////////////////////////////////////////////////////////////////////
// event.hxx
//
// Ben Storey
//
// A simpler Test class that fires some events and handles with some logging. 
//
///////////////////////////////////////////////////////////////////////////////////////

#include <string>
#include "event/event.hpp"
#include "event/eventManager.hpp"

namespace jimbo
{
    namespace test
    {

        class TestEvents : public EventHandler<TestEvents>
        {
            class TestEvent : public jimbo::Event<TestEvent>
            {
            public:
                TestEvent(std::string m, int num) : m_(m), n_(num) {  }
                virtual ~TestEvent() {  }

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

            bool testSubscribe()
            {
                addEventHandler<TestEvent>(&TestEvents::HandleEvent);

                mg_.raiseEvent(new TestEvent("TEST", 1));
                mg_.raiseEvent(new TestEvent("ANOTHER", 2));
                mg_.dispatchEvents();

                // Last result should have been two
                return lastResult_ == 2;
            }

            bool testRemoveHandler()
            {
                addEventHandler<TestEvent>(&TestEvents::HandleEvent);
                mg_.raiseEvent(new TestEvent("TEST", 1));
                mg_.dispatchEvents();

                removeEventHandler<TestEvent>();
                mg_.raiseEvent(new TestEvent("AFTER REMOVAL", 3));
                mg_.dispatchEvents();

                // We shouldn't have received the last result, so should still be 1
                return lastResult_ == 1;
            }

            bool testImmediateDispatch()
            {
                addEventHandler<TestEvent>(&TestEvents::HandleEvent);

                mg_.raiseEvent(new TestEvent("WE ARE BACK", 5));
                mg_.raiseEvent(new TestEvent("HOPEFULLY", 6));
                mg_.dispatchEvents();

                mg_.immediateDispatch(new TestEvent("Test Immediate Dispatch", 10));

                // no dispatchEvents() called, should still be 10 anyway
                return lastResult_ == 10;
            }

            bool testMultipleSubscribe()
            {

                // Should still receive event only once
                removeEventHandler<TestEvent>();
                removeEventHandler<TestEvent>();
                removeEventHandler<TestEvent>();

                // Make sure queue is clean
                mg_.dispatchEvents();

                // Add too many
                addEventHandler<TestEvent>(&TestEvents::HandleEvent);
                addEventHandler<TestEvent>(&TestEvents::HandleEvent);
                addEventHandler<TestEvent>(&TestEvents::HandleEvent);

                sum_ = 0;
                mg_.raiseEvent(new TestEvent("MULTIPLE SUBSCRIBE", 1));
                mg_.dispatchEvents();

                return sum_ == 1;
            }

            void HandleEvent(const TestEvent& theEvent)
            {
                lastResult_ = theEvent.getNumber();
                sum_ += lastResult_;
            }

        private:

            EventManager mg_;

            // For testing purposes
            int lastResult_ = 0;
            int sum_ = 0;
        };
    }
}

#endif // JIMBO_TEST_COMPONENT_EVENT_HPP