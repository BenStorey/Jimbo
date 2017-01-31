#pragma once

/////////////////////////////////////////////////////////
// Application.h
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
#include "Core/Application.h"

// Events
#include "Event/Event.h"
#include "Event/EventHandler.h"
#include "Event/EventManager.h"

// Input
#include "Input/KeyMapping.h"

// Scenes to override
#include "Scene/Scene.h"