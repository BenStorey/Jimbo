#pragma once

/////////////////////////////////////////////////////////
// Sound.h
//
// Ben Storey
//
// Represents a single sound, like an explosion sound effect or whatever. 
//
/////////////////////////////////////////////////////////

#include <string>

namespace Jimbo
{
	class Sound
	{
	public:
		enum class FileType { OGG, WAV };

		Sound(const std::string& filename, FileType type) : file_(filename), type_(type) {};
		~Sound();

		void LoadFromFile();
		void Free();

	private:

		std::string file_;
		FileType    type_;

		// For now, making all sounds non-copyable. 
		Sound(Sound const&) = delete;             // Copy construct
		Sound(Sound&&) = delete;                  // Move construct
		Sound& operator=(Sound const&) = delete;  // Copy assign
		Sound& operator=(Sound &&) = delete;      // Move assign
	};

}