
#ifndef JIMBO_INPUT_GLFW_GLFWINPUTMANAGER_HXX
#define JIMBO_INPUT_GLFW_GLFWINPUTMANAGER_HXX

/////////////////////////////////////////////////////////
// glfwInputManager.h
//
// Ben Storey
//
// Use this input manager when we're using glfw callbacks
//
/////////////////////////////////////////////////////////

#include <glfw3.h>
#include "input/inputmanager.hpp"

namespace jimbo
{
    class glfwInputManager : public InputManager
    {
    public:
        glfwInputManager(GLFWwindow* window) : window_(window) {}
        ~glfwInputManager() {}

        void initialise() override final
        {
            instance_ = this;
            glfwSetKeyCallback(window_, KeyCallback);
            glfwSetWindowCloseCallback(window_, WindowCloseCallback);
        }

        void shutdown() override final {}
        void update()   override final { glfwPollEvents(); }

    private:

        GLFWwindow* window_;

        // glfw takes callbacks to C functions. We can't give callbacks to member functions, but we can give them to static functions
        // Therefore we have a static object that we point to, and we let the wrapper call our callbacks
        static glfwInputManager* instance_;

        static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            // If it's handling a different window, we can ignore any events
            if (instance_->window_ != window) return;

            // Otherwise, dispatch to our parent functions
            switch (action)
            {
                case GLFW_PRESS:    instance_->keyJustPressed(static_cast<KeyMapping>(key), KeyModifier(mods)); break; 
                case GLFW_RELEASE:    instance_->keyJustReleased(static_cast<KeyMapping>(key), KeyModifier(mods)); break; 
                case GLFW_REPEAT:    instance_->keyRepeat(static_cast<KeyMapping>(key), KeyModifier(mods)); break;
                default: break; // ignore
            }
        }

        static void WindowCloseCallback(GLFWwindow* window)
        {
            instance_->windowCloseEvent();
        }

    };
}

#endif // JIMBO_INPUT_GLFW_GLFWINPUTMANAGER_HXX