/////////////////////////////////////////////////////////
// Renderer.cpp
//
// Ben Storey
//
// More of a placeholder right now..
//
/////////////////////////////////////////////////////////

#include <glfw3.h>
#include "Renderer.h"

void Jimbo::Renderer::startRenderFrame()
{
    // Nothing to do
}

void Jimbo::Renderer::endRenderFrame()
{
    glfwSwapBuffers(static_cast<GLFWwindow*>(window_));
}