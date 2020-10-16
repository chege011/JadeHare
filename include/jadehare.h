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
#include <cassert>

#include <glm/glm.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/norm.hpp>

#if defined(PBRT_BUILD_GPU_RENDERER) && defined(__CUDACC__)
#ifndef PBRT_NOINLINE
#define PBRT_NOINLINE __attribute__((noinline))
#endif
#define PBRT_CPU_GPU __host__ __device__
#define PBRT_GPU __device__
#if defined(PBRT_IS_GPU_CODE)
#define PBRT_CONST __device__ const
#else
#define PBRT_CONST const
#endif
#else
#define PBRT_CONST const
#define PBRT_CPU_GPU
#define PBRT_GPU
#endif

namespace jadehare {

    using FloatBits = uint32_t;

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

    using Point2f = Point2<float>;
    using Point2i = Point2<int>;
    using Point3f = Point3<float>;
    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int>;
    using Vector3f = Vector3<float>;

    class Quaternion;

    template<typename T>
    class Bounds2;

    using Bounds2f = Bounds2<float>;
    using Bounds2i = Bounds2<int>;

    template<typename T>
    class Bounds3;

    using Bounds3f = Bounds3<float>;
    using Bounds3i = Bounds3<int>;
}

#endif //JADEHARE_H
