/////////////////////////////////////////////////////////
// Application.cpp
//
// Ben Storey
//
// This is the implementation of our core Application class for all setup. It uses
// glfw for window management 
//
/////////////////////////////////////////////////////////

// We are going to be depending on glfw for window management. So that clients don't need to also have it in their include
// path, we include here in the cpp only. glad is used for OpenGL setup
#include <glad/glad.h>
#include <glfw3.h>

#include "application/application.h"
#include "util/logging.h"

// We are using the irrKlang audio engine for now, can move it out when we want to use something free...
#include "audio/irrKlang/irrklangsoundmanager.h"
#include "audio/silent/silentsoundmanager.h"
#include "input/glfw/glfwinputmanager.h"

Jimbo::Application::Application() noexcept
{
    // Defaults
    windowName_ = "Jimbo Project";
    audioEngine_ = AudioEngine::IRRKLANG;

    soundManager_ = nullptr;
    eventManager_ = nullptr;
    sceneManager_ = nullptr;
    inputManager_ = nullptr;
    renderer_      = nullptr;
}

Jimbo::Application::~Application() noexcept
{

}

void Jimbo::Application::initialise()
{
    // Switch depending on the choice
    switch (audioEngine_)
    {
    case AudioEngine::IRRKLANG:
        soundManager_.reset(new irrKlangSoundManager); break;
    case AudioEngine::SILENT:
        soundManager_.reset(new SilentSoundManager); break;
    }

    LOG("Initialising Sound Manager");
    if (!soundManager_->initialise())
    {
        // We couldn't initialise the given one. Therefore, use the debug one (that plays no sound)
        soundManager_.reset(new SilentSoundManager);
    }

    eventManager_.reset(new EventManager);

    if (!glfwInit())
    {
        LOG("Failed to initialize GLFW\n");
        throw new std::runtime_error("Jimbo - Failed to initialise GLFW");
    }

    initialised_ = true;
}

void Jimbo::Application::setupWindow()
{
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

    // Open a window and create its OpenGL context
    auto window = glfwCreateWindow(windowSizeX_, windowSizeY_, windowName_.c_str(), nullptr, nullptr);

    if (window == nullptr)
    {
        glfwTerminate();
        throw new std::runtime_error("Jimbo - Unable to create application window");
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    // Initialise Glad
    if (!gladLoadGL())
    {
        LOG("Failed to initialize Glad\n");
        throw new std::runtime_error("Jimbo - Failed to initialise OpenGL");
    }

    int width, height;
    glfwGetFramebufferSize(window, &width, &height);
    glViewport(0, 0, width, height);

    // Can now create our other input/scene managers that the window is available
    renderer_.reset(new Renderer(window));
    inputManager_.reset(new glfwInputManager(window));
    sceneManager_.reset(new SceneManager(renderer_.get(), inputManager_.get(), eventManager_.get(), soundManager_.get()));
}

void Jimbo::Application::run()
{
    LOG("Initialising Application");
    
    initialise();
    setupWindow();

    // Ensure everything is initialised before running
    inputManager_->initialise();

    // Push the first scene of the world. Scene manager will take ownership of the pointer from here
    sceneManager_->pushScene(startupScene_);

    // Main game loop
    sceneManager_->runGameLoop();

    LOG("Shutting down Application");
    soundManager_->shutdown();
    inputManager_->shutdown();

    glfwTerminate();
}