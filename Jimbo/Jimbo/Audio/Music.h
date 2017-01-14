#pragma once

/////////////////////////////////////////////////////////
// Music.h
//
// Ben Storey
//
// Music has its own class as it may need to support streaming / pausing etc which single sounds might not need
//
/////////////////////////////////////////////////////////

// TODO - Music and Sound should probably both inherit from an Audio class that has all this..
namespace Jimbo
{
	class Music
	{
	public:
		enum class FileType { OGG, WAV };

		Music(const std::string& filename, FileType type) : file_(filename), type_(type) {};
		~Music();

		void LoadFromFile();
		void Free();

	private:

		std::string file_;
		FileType    type_;

		// For now, making all sounds non-copyable. 
		Music(Music const&) = delete;             // Copy construct
		Music(Music&&) = delete;                  // Move construct
		Music& operator=(Music const&) = delete;  // Copy assign
		Music& operator=(Music &&) = delete;      // Move assign
	};

}