//
// Created by 1129 on 2020/9/25.
//

#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef JADEHARE_H
#define JADEHARE_H

#include <iostream>
#include <algorithm>
#include <glog/logging.h>

namespace jadehare {
#ifdef PBRT_FLOAT_AS_DOUBLE
    typedef double Float;
#else
    typedef float Float;
#endif  // PBRT_FLOAT_AS_DOUBLE

    template<typename T>
    class Vector2;

    template<typename T>
    class Vector3;

    template<typename T>
    class Point3;

    template<typename T>
    class Point2;

    template<typename T>
    class Normal3;

    class Ray;

    class RayDifferential;

    template<typename T>
    class Bounds2;

    template<typename T>
    class Bounds3;

    // Global Constants
#ifdef _MSC_VER
#define MaxFloat std::numeric_limits<Float>::max()
#define Infinity std::numeric_limits<Float>::infinity()
#else
static constexpr Float MaxFloat = std::numeric_limits<Float>::max();
static constexpr Float Infinity = std::numeric_limits<Float>::infinity();
#endif
#ifdef _MSC_VER
#define MachineEpsilon (std::numeric_limits<Float>::epsilon() * 0.5)
#else
static constexpr Float MachineEpsilon =
    std::numeric_limits<Float>::epsilon() * 0.5;
#endif
    static constexpr Float ShadowEpsilon = 0.0001f;
    static constexpr Float Pi = 3.14159265358979323846;
    static constexpr Float InvPi = 0.31830988618379067154;
    static constexpr Float Inv2Pi = 0.15915494309189533577;
    static constexpr Float Inv4Pi = 0.07957747154594766788;
    static constexpr Float PiOver2 = 1.57079632679489661923;
    static constexpr Float PiOver4 = 0.78539816339744830961;
    static constexpr Float Sqrt2 = 1.41421356237309504880;

    // Global Inline Functions
    inline uint32_t FloatToBits(float f) {
        uint32_t ui;
        memcpy(&ui, &f, sizeof(float));
        return ui;
    }

    inline float BitsToFloat(uint32_t ui) {
        float f;
        memcpy(&f, &ui, sizeof(uint32_t));
        return f;
    }

    inline uint64_t FloatToBits(double f) {
        uint64_t ui;
        memcpy(&ui, &f, sizeof(double));
        return ui;
    }

    inline double BitsToFloat(uint64_t ui) {
        double f;
        memcpy(&f, &ui, sizeof(uint64_t));
        return f;
    }

    inline float NextFloatUp(float v) {
        // Handle infinity and negative zero for _NextFloatUp()_
        if (std::isinf(v) && v > 0.) return v;
        if (v == -0.f) v = 0.f;

        // Advance _v_ to next higher float
        uint32_t ui = FloatToBits(v);
        if (v >= 0)
            ++ui;
        else
            --ui;
        return BitsToFloat(ui);
    }

    inline float NextFloatDown(float v) {
        // Handle infinity and positive zero for _NextFloatDown()_
        if (std::isinf(v) && v < 0.) return v;
        if (v == 0.f) v = -0.f;
        uint32_t ui = FloatToBits(v);
        if (v > 0)
            --ui;
        else
            ++ui;
        return BitsToFloat(ui);
    }

    inline double NextFloatUp(double v, int delta = 1) {
        if (std::isinf(v) && v > 0.) return v;
        if (v == -0.f) v = 0.f;
        uint64_t ui = FloatToBits(v);
        if (v >= 0.)
            ui += delta;
        else
            ui -= delta;
        return BitsToFloat(ui);
    }

    inline double NextFloatDown(double v, int delta = 1) {
        if (std::isinf(v) && v < 0.) return v;
        if (v == 0.f) v = -0.f;
        uint64_t ui = FloatToBits(v);
        if (v > 0.)
            ui -= delta;
        else
            ui += delta;
        return BitsToFloat(ui);
    }

    template<typename T, typename U, typename V>
    inline T Clamp(T val, U low, V high) {
        if (val < low)
            return low;
        else if (val > high)
            return high;
        else
            return val;
    }
}

#endif //JADEHARE_H
