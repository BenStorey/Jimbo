#pragma once

/////////////////////////////////////////////////////////
// Application.h
//
// Ben Storey
//
// This include file includes everything else in the Jimbo library, so a client project
// needs to include this file (and the compiled library) only
//
/////////////////////////////////////////////////////////


// Handy define to make logging easier, is compiled away in release
//#define LOG(x) Application::Instance()::Log(x, __FILE__, __LINE__ );

// Necessary libraries for clients to link against
#pragma comment(lib, "Glad.lib")
#pragma comment(lib, "glfw3.lib")

#include "Core\Types.h"
#include "Core\Application.h"
