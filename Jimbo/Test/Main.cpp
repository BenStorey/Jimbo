
/////////////////////////////////////////////////////////
// Main.cpp
//
// Ben Storey
//
// Entry point into our test project, for testing all Jimbo features. 
//
/////////////////////////////////////////////////////////


// Our Jimbo engine!
#include <jimbo.hpp>
using namespace jimbo;

#include <memory>
#include <boost/optional/optional.hpp>
#include <boost/scoped_ptr.hpp>
#include <cstdint>

// Testing
#include "test/testengine.hpp"
#include "log/logging.hpp"


#ifdef _WIN32

// jimbo includes boost::asio which includes windows.h
// #include <Windows.h>
// _In_ parameters match the signature, which prevents code analysis giving me warnings for not matching
int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ char*, _In_ int nShowCmd)
#else 
int main()
#endif
{

    // Execute all tests on startup
    jimbo::test::TestEngine te;
    te.executeAllTests();
    te.logTestResults();

    // Should be moved into here at some stage, so log details can be set in config too
    // For now, just instantiate ourselves to get beautiful logging...
    //app->logEvents();
    jimbo::log::EventLog logEvents;

    // Start demo application using our example TestScene
    boost::scoped_ptr<Application> app (new Application(new Config("../config.toml")));

    app->setStartupScene(new test::TestScene);
    
    // Should register resources here under normal circumstances
    //app->registerResource(RID("testSound"), new test::ResourceLoaderDelay(new ResourceFileLoader("../Assets/Success.wav"), std::chrono::milliseconds(5000)));
    //app->registerResource(RID("testMusic"), new ResourceFileLoader("../Assets/SomeMusic.ogg"));

    // All setup and good to go..
    app->run();

    return 0;
}