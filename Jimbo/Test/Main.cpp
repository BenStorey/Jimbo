
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

    // Start demo application using our example TestScene
    boost::scoped_ptr<Application> app (new Application);

    app->setFullScreen(false);
    app->setWindowSize(800, 600);
    app->setWindowName("Testing Engine");
    app->setAudioEngine(Application::AudioEngine::IRRKLANG);
    app->setStartupScene(new test::TestScene);
    app->capFrameRate(60);

    // We can register all of our resources in advance
    app->setResourceThreadPoolSize(4);

    // Should register resources here under normal circumstances
    app->registerResource(RID("testSound"), new test::ResourceLoaderDelay(new ResourceFileLoader("../Assets/Success.wav"), std::chrono::milliseconds(5000)));

    // This should probably be registerStreamableResource..
    app->registerResource(RID("testMusic"), new ResourceFileLoader("../Assets/SomeMusic.ogg"));

    // All setup and good to go..
    app->run();

    return 0;
}