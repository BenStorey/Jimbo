#pragma once

/////////////////////////////////////////////////////////
// AudioLoader.h
//
// Ben Storey
//
// Abstract class to be overriden by other classes for loading other file types
// For example to parse an OGG file, we'd use our OGGLoader to get into a buffer
//
/////////////////////////////////////////////////////////

#include <string>

namespace Jimbo
{
	class AudioLoader
	{
	public:
		virtual ~AudioLoader() {}
		virtual void loadFromFile(const std::string& file) = 0;
	};
}