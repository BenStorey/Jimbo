/////////////////////////////////////////////////////////
// Application.cpp
//
// Ben Storey
//
// This is the implementation of our core Application class for all setup. It uses
// glfw for window management 
//
/////////////////////////////////////////////////////////

#include "Application.h"
#include "Logging.h"

// We are going to be depending on glfw for window management. So that clients don't need to also have it in their include
// path, we include here in the cpp only. glad is used for OpenGL setup
#include <glad/glad.h>
#include <glfw3.h>

Jimbo::Application::Application()
{
	this->windowName = "Jimbo Project";
	this->fps = 0;
}

Jimbo::Application::~Application()
{
}

void Jimbo::Application::run()
{
	LOG("Initialising Application");

	if (!glfwInit())
	{
		LOG("Failed to initialize GLFW\n");
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

    // Open a window and create its OpenGL context
	GLFWwindow* window; 
	window = glfwCreateWindow(windowSizeX, windowSizeY, windowName.c_str(), nullptr, nullptr);
	
	if (window == nullptr) 
	{
		glfwTerminate();
		return;
	}
	
	glfwMakeContextCurrent(window); 
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	// Initialise Glad
	if (!gladLoadGL())
	{
		LOG("Failed to initialize Glad\n");
		return;
	}

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	while (!glfwWindowShouldClose(window))
	{
		glfwPollEvents();

		// Close on ESC
		if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		{
			glfwSetWindowShouldClose(window, GL_TRUE);
		}

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		// Swap buffers
		glfwSwapBuffers(window);
	}

	LOG("Shutting down Application");
	glfwTerminate();
}