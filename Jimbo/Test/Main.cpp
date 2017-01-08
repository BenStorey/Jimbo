
/////////////////////////////////////////////////////////
// Main.cpp
//
// Ben Storey
//
// Entry point into our test project, for testing all Jimbo features. 
//
/////////////////////////////////////////////////////////

#include <memory>

// Our Jimbo engine!
#include <Jimbo.h>
using namespace Jimbo;

#ifdef _WIN32
#include <Windows.h>
	int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd)
#else 
	int main()
#endif
{

	std::unique_ptr<Application> app(new Application());
	app->setFullScreen(false);
	app->setWindowSize(800, 600);
	app->setWindowName("Testing Engine");
	
	// And then run the app...
	app->run();

	return 0;
}