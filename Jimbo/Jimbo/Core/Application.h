#pragma once

/////////////////////////////////////////////////////////
// Application.h
//
// Ben Storey
//
// This is the entry point for running a Jimbo game. Controls the window and controls the scene management,
// and manages startup settings. I don't like global singleton classes usually, and this should be the only one. 
//
/////////////////////////////////////////////////////////

#include <string>
#include <iostream>
#include "Types.h"

// We rely on GLFX and Glad for our application

namespace Jimbo
{

	class Application
	{

	public:

		Application();
		~Application();

		//void run(ScenePtr);
		void run();

		// Window modes
		void setWindowName(const std::string& name)	{ this->windowName = name; };
		void setFullScreen(bool isFullScreen)		{ this->fullScreen = isFullScreen; };
		void setWindowSize(int x, int y)			{ windowSizeX = x; windowSizeY = y; }
		void capFrameRate (int fps)					{ this->fps = fps; }

		//Surface* GetScreen();
		//SceneManagerPtr GetSceneManager();
		//EventManagerPtr GetEventManager();
		//SoundManagerPtr GetSoundManager();

		//std::string GetAppExePath();

	private:

		// Can't copy our Application around
		Application(Application const&) = delete;             // Copy construct
		Application(Application&&) = delete;                  // Move construct
		Application& operator=(Application const&) = delete;  // Copy assign
		Application& operator=(Application &&) = delete;      // Move assign

		//SceneManagerPtr sceneManager;
		//EventManagerPtr eventManager;
		//SoundManagerPtr soundManager;
		//Surface* screen;

		bool initialized;
		bool fullScreen;
		std::string windowName;
		int fps;

		int windowSizeX;
		int windowSizeY;
	};

	//inline Surface*		   Application::GetScreen(void) { return screen; }
	//inline SceneManagerPtr Application::GetSceneManager(void) { return sceneManager; }
	//inline EventManagerPtr Application::GetEventManager(void) { return eventManager; }
	//inline SoundManagerPtr Application::GetSoundManager(void) { return soundManager; }

}