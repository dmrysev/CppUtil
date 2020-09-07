#pragma once

#include <string>
#include <cstdlib>
#include <limits>
#include <type_traits>

namespace Util {

    template <class T>
    T limit(T value, T min, T max)
    {
        return value < min ? min :
               value > max ? max :
                             value;
    }

    template<class T>
    typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
        almostEqual(T x, T y)
    {
        return std::abs(x - y) < std::numeric_limits<T>::epsilon();
    }

    inline bool isDouble(const std::string& s)
    {
        char* end = nullptr;
        strtod(s.c_str(), &end);
        return end != s.c_str() && *end == '\0';
    }

}
