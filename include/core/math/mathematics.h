//
// Created by chege on 2020/10/12.
//

#ifndef JADEHARE_CORE_MATH_H
#define JADEHARE_CORE_MATH_H

namespace jadehare {
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
    inline typename std::enable_if_t<std::is_floating_point<T>::value, bool> IsNaN(T v) {
        return std::isnan(v);
    }

    template<typename T>
    inline typename std::enable_if_t<std::is_integral<T>::value, bool> IsNaN(T v) {
        return false;
    }

    // Math Inline Functions
    inline float Lerp(float t, float a, float b) {
        return (1 - t) * a + t * b;
    }

    inline constexpr float gamma(int n) {
        return (n * MachineEpsilon) / (1 - n * MachineEpsilon);
    }

    template<typename T>
    inline typename std::enable_if_t<std::is_floating_point<T>::value, bool>
    IsInf(T v) {
        return std::isinf(v);
    }

    template<class To, class From>
    PBRT_CPU_GPU typename std::enable_if_t<sizeof(To) == sizeof(From) &&
                                           std::is_trivially_copyable_v<From> &&
                                           std::is_trivially_copyable_v<To>,
            To>
    bit_cast(const From &src) noexcept {
        static_assert(std::is_trivially_constructible_v<To>,
                      "This implementation requires the destination type to be trivially "
                      "constructible");
        To dst;
        std::memcpy(&dst, &src, sizeof(To));
        return dst;
    }

    inline uint32_t FloatToBits(float f) {
#ifdef PBRT_IS_GPU_CODE
        return __float_as_uint(f);
#else
        return pstd::bit_cast<uint32_t>(f);
#endif
    }

    PBRT_CPU_GPU
    inline float NextFloatUp(float v) {
        // Handle infinity and negative zero for _NextFloatUp()_
        if (IsInf(v) && v > 0.)
            return v;
        if (v == -0.f)
            v = 0.f;

        // Advance _v_ to next higher float
        uint32_t ui = FloatToBits(v);
        if (v >= 0)
            ++ui;
        else
            --ui;
        return BitsToFloat(ui);
    }

    PBRT_CPU_GPU
    inline float NextFloatDown(float v) {
        // Handle infinity and positive zero for _NextFloatDown()_
        if (IsInf(v) && v < 0.)
            return v;
        if (v == 0.f)
            v = -0.f;
        uint32_t ui = FloatToBits(v);
        if (v > 0)
            --ui;
        else
            ++ui;
        return BitsToFloat(ui);
    }
}

#endif //JADEHARE_UTIL_MATH_H
