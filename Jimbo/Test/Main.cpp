
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
#include <test/testengine.hpp>

#include <memory>
#include <boost/scoped_ptr.hpp>

using namespace jimbo;


#ifdef _WIN32

// jimbo includes boost::asio which includes windows.h
#include <Windows.h>

// _In_ parameters match the signature, which prevents code analysis giving me warnings for not matching
int __stdcall WinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ char*, _In_ int nShowCmd)
#else 
int main()
#endif
{    
    // Execute all tests on startup
    test::TestEngine te;
    te.executeAllTests();
    te.logTestResults();

    // This file needs to be saved without the UTF BOM. Which I think means it can't be edited within VS - annoying!
    Config* config = new Config("config.toml");
    boost::scoped_ptr<Application> app(new Application(config));

    app->setStartupScene(new test::TestScene);
    
    //app->registerResource(RID("testMusic"), app->musicResource(), new ResourceFileLoader("../Assets/SomeMusic.ogg"));

    app->run();

    return 0;
}