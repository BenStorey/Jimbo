#pragma once

/////////////////////////////////////////////////////////
// Renderer.h
//
// Ben Storey
//
// More of a placeholder right now. The void* is obviously not ideal, but I don't want to build
// a whole lot of subclasses to implement a Renderer interface just now. We're always a GLFWwindow* so can cast to it 
//
/////////////////////////////////////////////////////////

namespace jimbo
{
    class Renderer
    {
    public:
        Renderer(void* window) : window_(window) {}

        void startRenderFrame();
        void endRenderFrame();

    private:

        void* window_;
    };
}