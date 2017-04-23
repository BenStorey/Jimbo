
#ifndef JIMBO_UTIL_STRINGHASH_HXX
#define JIMBO_UTIL_STRINGHASH_HXX

/////////////////////////////////////////////////////////
// stringhash.hxx
//
// Ben Storey
//
// Hashes a string AT COMPILE TIME! Useful where we want constexpr to use integer in production
// and a string during debug time. Resource IDs are generated this way for example
//
/////////////////////////////////////////////////////////

#include <cstdint>

namespace jimbo 
{
    namespace util
    {

        // Implementation is from the link below! (with thanks!)
        // http://codereview.stackexchange.com/questions/124295/compile-time-string-hash
        class StringHash
        {
        public:

            // Public interface, only function that should be called directly
            // https://en.wikipedia.org/wiki/Jenkins_hash_function
            static constexpr std::uint32_t compileTimeJenkinsStringHash(const char * cstr) noexcept
            {
                return hashImpl(cstr, stringLength(cstr), 0);
            }

        private:

            static constexpr std::uint32_t stringLength(const char * cstr) noexcept
            {
                return (*cstr != '\0') ? (stringLength(cstr + 1) + 1) : 0;
            }

            static constexpr std::uint32_t sumSHL(std::uint32_t h, std::uint32_t shift) noexcept { return h + (h << shift); }
            static constexpr std::uint32_t sumSHR(std::uint32_t h, std::uint32_t shift) noexcept { return h + (h >> shift); }
            static constexpr std::uint32_t xorSHR(std::uint32_t h, std::uint32_t shift) noexcept { return h ^ (h >> shift); }

            static constexpr std::uint32_t hashFinishImpl(std::uint32_t h) noexcept
            {
                // h += (h <<  3)
                // h ^= (h >> 11)
                // h += (h << 15)
                return sumSHL(xorSHR(sumSHL(h, 3), 11), 15);
            }

            static constexpr std::uint32_t hashStepImpl(std::uint32_t h, std::uint32_t c) noexcept
            {
                // h += c
                // h += (h << 10)
                // h ^= (h >>  6)
                return xorSHR(sumSHL(h + c, 10), 6);
            }

            static constexpr std::uint32_t hashImpl(const char * cstr, std::uint32_t length, std::uint32_t h) noexcept
            {
                return (length != 0) ? hashImpl(cstr + 1, length - 1, hashStepImpl(h, *cstr)) : hashFinishImpl(h);
            }
        };
    }
}

#endif // JIMBO_UTIL_STRINGHASH_HXX