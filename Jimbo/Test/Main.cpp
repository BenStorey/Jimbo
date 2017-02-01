
/////////////////////////////////////////////////////////
// Main.cpp
//
// Ben Storey
//
// Entry point into our test project, for testing all Jimbo features. 
//
/////////////////////////////////////////////////////////

#include <memory>
#include <boost/optional/optional.hpp>
#include <boost/scoped_ptr.hpp>

// Our Jimbo engine!
#include <jimbo.h>
using namespace jimbo;

// Testing
#include "test/testevents.h"
#include "test/testscene.h"

#ifdef _WIN32
#include <Windows.h>
int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else 
int main()
#endif
{
    // Testing event manager
    TestEvents te;
    te.doTest();

    boost::scoped_ptr<Application> app (new Application);
    app->setFullScreen(false);
    app->setWindowSize(800, 600);
    app->setWindowName("Testing Engine");
    app->setAudioEngine(Application::AudioEngine::IRRKLANG);
    app->setStartupScene(new TestScene);

    app->capFrameRate(60);

    app->run();

    return 0;
}