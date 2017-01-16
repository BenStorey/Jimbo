
/////////////////////////////////////////////////////////
// Main.cpp
//
// Ben Storey
//
// Entry point into our test project, for testing all Jimbo features. 
//
/////////////////////////////////////////////////////////

#include <memory>
#include <boost\optional\optional.hpp>

// Our Jimbo engine!
#include <Jimbo.h>
using namespace Jimbo;

// Testing
#include "Test/TestEvents.h"

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

	auto app = std::make_unique<Application>();
	app->setFullScreen(false);
	app->setWindowSize(800, 600);
	app->setWindowName("Testing Engine");

	app->capFrameRate(60);

	app->run();

	return 0;
}