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
#include <memory>
#include <boost/optional/optional.hpp>

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
		void setWindowName(const std::string& name)	{ this->windowName_ = name; };
		void setFullScreen(bool isFullScreen)		{ this->fullScreen_ = isFullScreen; };
		void setWindowSize(int x, int y)			{ windowSizeX_ = x; windowSizeY_ = y; }
		
		// Use optional for framerates, as you can pass an empty to turn it off
		void capFrameRate(boost::optional<int> fps)	{ this->fps_ = fps; }
		void capFrameRate(int fps)					{ this->fps_ = boost::make_optional(fps); }
		boost::optional<int> getFrameRate()			{ return fps_; }

		//Surface* GetScreen();
		//SceneManagerPtr GetSceneManager();
		//EventManagerPtr GetEventManager();
		//SoundManagerPtr GetSoundManager();

		//std::string GetAppExePath();

		// Can't copy our Application around. Notice that these are defined in public and not private,
		// since that will lead to better error messages if anyone tries to use them!
		Application(Application const&) = delete;             // Copy construct
		Application(Application&&) = delete;                  // Move construct
		Application& operator=(Application const&) = delete;  // Copy assign
		Application& operator=(Application &&) = delete;      // Move assign

	private:

		void initialise();

		//SceneManagerPtr sceneManager;
		//EventManagerPtr eventManager;
		//SoundManagerPtr soundManager;
		//Surface* screen;

		// Use unique pointer because we want ownership of it. 
		//std::unique_ptr<SoundManager> soundManager_;

		bool initialised_;
		bool fullScreen_;
		std::string windowName_;
		boost::optional<int> fps_;

		int windowSizeX_;
		int windowSizeY_;
	};

	//inline Surface*		   Application::GetScreen(void) { return screen; }
	//inline SceneManagerPtr Application::GetSceneManager(void) { return sceneManager; }
	//inline EventManagerPtr Application::GetEventManager(void) { return eventManager; }
	//inline SoundManagerPtr Application::GetSoundManager(void) { return soundManager; }

}