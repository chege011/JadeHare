//
// Created by chege on 2020/10/12.
//

#ifndef JADEHARE_CORE_MATH_H
#define JADEHARE_CORE_MATH_H

namespace jadehare{
    // Mathematical Constants
    constexpr float ShadowEpsilon = 0.0001f;

    constexpr float Pi = 3.14159265358979323846;
    constexpr float InvPi = 0.31830988618379067154;
    constexpr float Inv2Pi = 0.15915494309189533577;
    constexpr float Inv4Pi = 0.07957747154594766788;
    constexpr float PiOver2 = 1.57079632679489661923;
    constexpr float PiOver4 = 0.78539816339744830961;
    constexpr float Sqrt2 = 1.41421356237309504880;

    // Floating-point Constants
    static constexpr float Infinity = std::numeric_limits<float>::infinity();

    static constexpr float MachineEpsilon = std::numeric_limits<float>::epsilon() * 0.5;

    // Floating-point Inline Functions
    template<typename T>
    inline typename std::enable_if_t<std::is_floating_point<T>::value, bool> IsNaN(T v)
    {
        return std::isnan(v);
    }

    template<typename T>
    inline typename std::enable_if_t<std::is_integral<T>::value, bool> IsNaN(T v)
    {
        return false;
    }

    // Math Inline Functions
    inline float Lerp(float t, float a, float b) {
        return (1 - t) * a + t * b;
    }

    inline constexpr float gamma(int n) {
        return (n * MachineEpsilon) / (1 - n * MachineEpsilon);
    }
}

#endif //JADEHARE_UTIL_MATH_H
