
#ifndef JIMBO_UTIL_BUFFER_HXX
#define JIMBO_UTIL_BUFFER_HXX

/////////////////////////////////////////////////////////
// buffer.hxx
//
// Ben Storey
//
// Definition of a buffer class to ensure we are consistent throughout jimbo
// We might eventually need to make this smarter to work with a proper allocator
// and put loaded memory into the right place (avoid fragmentation etc)
//
/////////////////////////////////////////////////////////

#include <vector>

namespace jimbo
{
    using Buffer = std::vector<char>;
}


#endif // JIMBO_UTIL_BUFFER_HXX