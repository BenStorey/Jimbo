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

#include "application/application.hpp"
#include "util/logging.hpp"

// We are using the irrKlang audio engine for now, can move it out when we want to use something free...
#include "event/eventmanager.hpp"
#include "graphics/renderer.hpp"
#include "scene/scene.hpp"
#include "scene/scenemanager.hpp"
#include "audio/irrKlang/irrklangsoundmanager.hxx"
#include "audio/silent/silentsoundmanager.hxx"
#include "input/glfw/glfwinputmanager.hxx"
#include "resource/resourcemanager.hpp"

jimbo::Application::Application() 
{
    // Defaults
    windowName_ = "Jimbo Project";
    audioEngine_ = AudioEngine::IRRKLANG;
    serviceLocator_.reset(new ServiceLocator);

    // We set this right away, as then resource related setup calls can be passed along to the resource manager
    serviceLocator_->setService(new ResourceManager);
}

jimbo::Application::~Application() 
{

}

void jimbo::Application::setResourceThreadPoolSize(int numThreads)
{
    serviceLocator_->resourceManager()->setThreadPoolSize(numThreads);
}

void jimbo::Application::registerResource(ResourceID id, ResourceLoader * loader)
{
    serviceLocator_->resourceManager()->registerResource(id, loader);
}

void jimbo::Application::initialise()
{
    // Switch depending on the choice
    switch (audioEngine_)
    {
    case AudioEngine::IRRKLANG:
        serviceLocator_->setService(new irrKlangSoundManager); break;
    case AudioEngine::SILENT:
        serviceLocator_->setService(new SilentSoundManager); break;
    }

    LOG("Initialising Sound Manager");
    if (!serviceLocator_->soundManager()->initialise())
    {
        // We couldn't initialise the given one. Therefore, use the debug one (that plays no sound)
        serviceLocator_->setService(new SilentSoundManager);
    }

    LOG("Initialising Resource Manager")
    serviceLocator_->resourceManager()->initialise();

    serviceLocator_->setService(new EventManager);

    if (!glfwInit())
    {
        LOG("Failed to initialize GLFW\n");
        throw new std::runtime_error("Jimbo - Failed to initialise GLFW");
    }

    initialised_ = true;
}


void jimbo::Application::setupWindow()
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
    serviceLocator_->setService(new Renderer(window));
    serviceLocator_->setService(new glfwInputManager(window));
    serviceLocator_->setService(new SceneManager(serviceLocator_.get()));
}

void jimbo::Application::run()
{
    LOG("Initialising Application");
    
    initialise();
    setupWindow();

    // Ensure everything is initialised before running
    serviceLocator_->inputManager()->initialise();

    // Push the first scene of the world. Scene manager will take ownership of the pointer from here
    serviceLocator_->sceneManager()->pushScene(std::move(startupScene_));

    // Main game loop
    serviceLocator_->sceneManager()->runGameLoop();

    LOG("Shutting down Application");
    serviceLocator_->soundManager()->shutdown();
    serviceLocator_->inputManager()->shutdown();
    serviceLocator_->resourceManager()->shutdown();

    glfwTerminate();
}