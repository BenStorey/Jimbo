# Jimbo

A simple OpenGL game engine/framework I'm putting together for a few small games I want to write. Uses Modern C++ and plenty of STL / Boost. 

## Building on other platforms

This project is still in it's early stages and so far I've only built it with Visual Studio 2015. All libraries are cross platform and the code also should be portable, although I haven't yet spent the time to create CMake files and a better directory structure. For example right now all headers and cpp files live in the same directories, it can't yet reasonably be installed as a library for other projects to build on top of.