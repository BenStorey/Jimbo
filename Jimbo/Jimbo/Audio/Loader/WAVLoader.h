#pragma once

/////////////////////////////////////////////////////////
// WAVLoader.h
//
// Ben Storey
//
// Class for loading WAV files into a buffer
//
/////////////////////////////////////////////////////////

#include "AudioLoader.h"

namespace Jimbo
{
	class WAVLoader : public AudioLoader
	{
		virtual void loadFromFile(const std::string& file);
	};
}