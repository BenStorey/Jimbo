
#ifndef JIMBO_TEST_COMPONENT_RESOURCELOADER_HXX
#define JIMBO_TEST_COMPONENT_RESOURCELOADER_HXX

///////////////////////////////////////////////////////////////////////////////////////
// resourceloader.hxx
//
// Ben Storey
//
// A wrapper around another loader, but that can give an arbitrary delay before
// returning results. Helpful when testing. 
//
///////////////////////////////////////////////////////////////////////////////////////

#include "resource/resourcedatasource.hpp"
#include "resource/resourceid.hpp"

// For sleeping
#include <thread>
#include <chrono>


namespace jimbo
{
    namespace test
    {
        /*
        class ResourceLoaderDelay : public jimbo::ResourceLoader
        {
        public:

            ResourceLoaderDelay(ResourceLoader* loader, std::chrono::milliseconds delay) : wrappedLoader_(loader), millisToSleep_(delay) { }

            std::unique_ptr<Resource> load(ResourceID id) override
            {
                std::this_thread::sleep_for(millisToSleep_);
                auto r = wrappedLoader_->load(id);
                return r;
            }

        private:

            std::unique_ptr<ResourceLoader> wrappedLoader_;
            std::chrono::milliseconds millisToSleep_;
        };
        */
    }
}

#endif // JIMBO_TEST_COMPONENT_RESOURCELOADER_HXX