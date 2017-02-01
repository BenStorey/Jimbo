/////////////////////////////////////////////////////////
// Renderer.cpp
//
// Ben Storey
//
// More of a placeholder right now..
//
/////////////////////////////////////////////////////////

#include <glfw3.h>
#include "graphics/renderer.h"

void jimbo::Renderer::startRenderFrame()
{
    // Nothing to do
}

void jimbo::Renderer::endRenderFrame()
{
    glfwSwapBuffers(static_cast<GLFWwindow*>(window_));
}