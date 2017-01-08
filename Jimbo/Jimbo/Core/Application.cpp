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
	if (!glfwInit())
	{
		return;
	}

	glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // We want OpenGL 3.3
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); //We don't want the old OpenGL 

    // Open a window and create its OpenGL context
	GLFWwindow* window; // (In the accompanying source code, this variable is global)
	window = glfwCreateWindow(windowSizeX, windowSizeY, windowName.c_str(), NULL, NULL);
	if (window == NULL) 
	{
		glfwTerminate();
		return;
	}
	
	glfwMakeContextCurrent(window); // Initialize GLEW
	
	glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

	do {
		// Draw nothing, see you in tutorial 2 !

		// Swap buffers
		glfwSwapBuffers(window);
		glfwPollEvents();

	} // Check if the ESC key was pressed or the window was closed
	while (glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS &&
		glfwWindowShouldClose(window) == 0);
}