
#ifndef JIMBO_ENGINE_HPP
#define JIMBO_ENGINE_HPP

/////////////////////////////////////////////////////////
// Jimbo.hpp
//
// Ben Storey
//
// This include file includes everything else in the Jimbo library, so a client project
// needs to include this file (and the compiled library) only.
// There should be no includes specific to an API implementation or external library, else I won't be able to swap them out later
//
/////////////////////////////////////////////////////////


// Necessary libraries for clients to link against
#pragma comment(lib, "Glad.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "irrKlang.lib")

// Include the rest of our engine so client doesn't have to
#include "application/application.hpp"

// Events
#include "event/event.hpp"
#include "event/eventhandler.hpp"
#include "event/eventmanager.hpp"

// Input
#include "input/keymapping.hpp"

// Scenes to override
#include "scene/scene.hpp"

#endif // JIMBO_ENGINE_HPP