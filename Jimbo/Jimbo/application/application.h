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
#include <boost/noncopyable.hpp>

#include "audio/soundManager.h"
#include "scene/scene.h"
#include "input/inputManager.h"
#include "graphics/renderer.h"

// We rely on GLFX and Glad for our application

namespace jimbo
{

    class Application : boost::noncopyable
    {

    public:

        enum class AudioEngine { IRRKLANG, SILENT };

        Application() noexcept;
        ~Application() noexcept;

        void run();

        // Window modes
        void setWindowName(const std::string& name) { this->windowName_ = name; };
        void setFullScreen(bool isFullScreen)       { this->fullScreen_ = isFullScreen; };
        void setWindowSize(int x, int y)            { windowSizeX_ = x; windowSizeY_ = y; }

        // Audio choices
        void setAudioEngine(AudioEngine ae)         { audioEngine_ = ae; }

        // Initial scene
        void setStartupScene(Scene* scene)          { startupScene_ = scene; }

        // Use optional for framerates, as you can pass an empty to turn it off
        void capFrameRate(boost::optional<int> fps) { this->fps_ = fps; }
        void capFrameRate(int fps)                  { this->fps_ = boost::make_optional(fps); }
        boost::optional<int> getFrameRate() const   { return fps_; }

    private:

        void initialise();
        void setupWindow();

        Scene* startupScene_;

        // Use unique pointer because we want ownership of it. 
        AudioEngine audioEngine_;
        std::unique_ptr<SoundManager> soundManager_;
        std::unique_ptr<SceneManager> sceneManager_;
        std::unique_ptr<EventManager> eventManager_;
        std::unique_ptr<InputManager> inputManager_;
        std::unique_ptr<Renderer>     renderer_;

        bool initialised_;
        bool fullScreen_;
        std::string windowName_;
        boost::optional<int> fps_;

        int windowSizeX_;
        int windowSizeY_;
    };
}