//
// Created by chege on 2020/10/6.
//

#ifndef JADEHARE_UTIL_FLOAT_H
#define JADEHARE_UTIL_FLOAT_H

#include <jadehare.h>

namespace jadehare
{
    // Floating-point Inline Functions
    template<typename T>
    inline typename std::enable_if_t<std::is_floating_point<T>::value, bool> IsNaN(T v)
    {
        return std::isnan(v);
    }

    template<typename T>
    inline PBRT_CPU_GPU typename std::enable_if_t<std::is_integral<T>::value, bool> IsNaN(T v)
    {
        return false;
    }
}

#endif //JADEHARE_UTIL_FLOAT_H
