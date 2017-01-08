#pragma once

/////////////////////////////////////////////////////////
// Logging.h
//
// Ben Storey
//
// Static logging class to help debugging
//
/////////////////////////////////////////////////////////

#include <string>
#include <experimental\filesystem>

#ifdef _WIN32
	#include <Windows.h>
#endif

// Helper if you want file/line numbers
#define LOG(x) Jimbo::Log::d(x, __FILE__, __LINE__ );

namespace Jimbo
{
	class Log
	{
	public:

		static void d(const std::string& s, const char* file, int lineNumber)
		{
#ifdef _DEBUG
			std::experimental::filesystem::path p(file);
			std::string toPrint = s + " (" + std::string(p.filename().string()) + ":" + std::to_string(lineNumber) + ")\n";
			d(toPrint);
#endif
		}

		static void d(const std::string& s)
		{
			#ifdef _DEBUG
				#ifdef _WIN32
			OutputDebugString(s.c_str());
				#endif
			#endif
		}
	};

}