#pragma once

/////////////////////////////////////////////////////////
// InputListener.h
//
// Ben Storey
//
// For objects that listen to input events. InputManager's will call them back as appropriate
//
/////////////////////////////////////////////////////////

namespace jimbo
{
    class InputListener
    {
    public:
        // Keys
        virtual void onKeyJustPressed(int action) = 0;
        virtual void onKeyJustReleased(int action) = 0;
        virtual void onKeyRepeat(int action) = 0;

        // Mouse todo..

        // Window events
        virtual void onWindowCloseEvent() = 0;
    };
}