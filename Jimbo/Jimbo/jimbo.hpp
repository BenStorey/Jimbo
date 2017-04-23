
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
// FYI on glfw3.lib, it should be the debug build, the downloaded version attempts to link to MSVCRT
// which in dev gives warning: LINK : warning LNK4098: defaultlib 'MSVCRT' conflicts with use of other libs; use /NODEFAULTLIB:library
#pragma comment(lib, "Glad.lib")
#pragma comment(lib, "glfw3.lib")
#pragma comment(lib, "OpenAL32.lib")
#pragma comment(lib, "irrKlang.lib")


// Include the rest of our engine so client doesn't have to
#include "application/application.hpp"
#include "application/config.hpp"

// Events
#include "event/event.hpp"
#include "event/eventhandler.hpp"
#include "event/eventmanager.hpp"

// Input
#include "input/keymapping.hpp"
#include "input/inputsettings.hpp"

// Scenes to override
#include "scene/scene.hpp"

// Resources
#include "resource/resourceid.hpp"
#include "resource/resource.hpp"
#include "resource/resourcemanager.hpp"
#include "resource/loader/fileloader.hpp"
#include "resource/proxy.hpp"

#endif // JIMBO_ENGINE_HPP