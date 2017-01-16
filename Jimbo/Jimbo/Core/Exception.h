#pragma once

/////////////////////////////////////////////////////////
// JimboException.h
//
// Ben Storey
//
// For the most part we don't make heavy use of exceptions, so this one class should literally be enough
// If missing assets for example we should do our best. If we can't startup at all, then throw this
//
/////////////////////////////////////////////////////////

#include <string>

namespace Jimbo
{
	class JimboException
	{
	public:
		JimboException(const std::string& message) : message_(message) {}
		const std::string& getMessage() const { return message_; }

	private:
		std::string message_;
	};
}