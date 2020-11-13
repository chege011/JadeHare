//
// Created by 1129 on 2020/10/16.
//

#ifndef JADEHARE_CORE_MATH_VECTOR_H
#define JADEHARE_CORE_MATH_VECTOR_H

#include "tuple.h"

namespace jadehare {

    // Vector2 Definition
    template<typename T>
    class Vector2 : public Tuple2<Vector2, T> {
    public:
        // Vector2 Public Methods
        using Tuple2<Vector2, T>::x;
        using Tuple2<Vector2, T>::y;

        Vector2() = default;

        Vector2(T x, T y) : Tuple2<Vector2, T>{x, y} {}

        template<typename U>
        explicit Vector2(const Point2<U> &p) : Tuple2<Vector2, T>(T(p.x), T(p.y)) {}

        template<typename U>
        explicit Vector2(const Vector2<U> &v) : Tuple2<Vector2, T>(T(v.x), T(v.y)) {}
    };

    // Vector3 Definition
    template<typename T>
    class Vector3 : public Tuple3<Vector3, T> {
    public:
        // Vector3 Public Methods
        using Tuple3<Vector3, T>::x;
        using Tuple3<Vector3, T>::y;
        using Tuple3<Vector3, T>::z;

        Vector3() = default;

        Vector3(T x, T y, T z) : Tuple3<Vector3, T>(x, y, z) {}

//        explicit Vector3(glm::vec<3, T, glm::defaultp> v) : Tuple3<Vector3, T>(v.x, v.y, v.z)
//        {}

        template<typename U>
        explicit Vector3(const Vector3<U> &v) : Tuple3<Vector3, T>(T(v.x), T(v.y), T(v.z)) {}

        template<typename U>
        explicit Vector3(const Point3<U> &p): Tuple3<Vector3, T>(T(p.x), T(p.y), T(p.z)) {}

        template<typename U>
        explicit Vector3(const Normal3<U> &n): Tuple3<Vector3, T>(T(n.x), T(n.y), T(n.z)) {}
    };

    // Vector2* definitions
    using Vector2f = Vector2<float>;
    using Vector2i = Vector2<int>;

// Vector3* definitions
    using Vector3f = Vector3<float>;
    using Vector3i = Vector3<int>;

    // Vector3fi Definition

#pragma region Vector2 Inline Functions
// Vector2 Inline Functions

    template<typename T>
    inline auto Dot(const Vector2<T> &v1, const Vector2<T> &v2) -> float {
        DCHECK(!v1.HasNaN() && !v2.HasNaN());
        return glm::dot(v1, v2);
    }

    template<typename T>
    inline auto AbsDot(const Vector2<T> &v1, const Vector2<T> &v2) -> float {
        DCHECK(!v1.HasNaN() && !v2.HasNaN());
        return glm::abs(Dot(v1, v2));
    }

    template<typename T>
    inline auto LengthSquared(const Vector2<T> &v) -> float {
        return Dot(v, v);
    }

    template<typename T>
    inline auto Length(const Vector2<T> &v) -> float {
        return glm::length2(v);
    }

    template<typename T>
    inline auto Normalize(const Vector2<T> &v) -> Vector2<float> {
        return v / Length(v);
    }

    template<typename T>
    inline auto Distance(const Point2<T> &p1, const Point2<T> &p2) -> float {
        return glm::distance(p1, p2);
    }

    template<typename T>
    inline auto DistanceSquared(const Point2<T> &p1, const Point2<T> &p2) -> float {
        return glm::distance2(p1, p2);
    }

#pragma endregion Vector2 Inline Functions

#pragma region Vector3 Inline Functions

// Vector3 Inline Functions

    template<typename T>
    inline Vector3<T> Cross(const Vector3<T> &v1, const Normal3<T> &v2) {
        DCHECK(!v1.HasNaN() && !v2.HasNaN());
        auto v3 = glm::cross(v1, v2);
        return v3;
    }

    template<typename T>
    inline Vector3<T> Cross(const Normal3<T> &v1, const Vector3<T> &v2) {
        DCHECK(!v1.HasNaN() && !v2.HasNaN());
        return glm::cross(v1, v2);
    }

    template<typename T>
    inline Vector3<T> Cross(const Vector3<T> &v, const Vector3<T> &w) {
        DCHECK(!v.HasNaN() && !w.HasNaN());
        return glm::cross(v1, v2);
    }

    template<typename T>
    inline T LengthSquared(const Vector3<T> &v) {
        return v.x * v.x + v.y * v.y + v.z * v.z;
    }

    template<typename T>
    inline auto Length(const Vector3<T> &v) -> float {
        using std::sqrt;
        return sqrt(LengthSquared(v));
    }

    template<typename T>
    inline Vector3<T> Normalize(const Vector3<T> &v) {
        return v / Length(v);
    }

    template<typename T>
    inline T Dot(const Vector3<T> &v, const Vector3<T> &w) {
        DCHECK(!v.HasNaN() && !w.HasNaN());
        return v.x * w.x + v.y * w.y + v.z * w.z;
    }

// Equivalent to std::acos(Dot(a, b)), but more numerically stable.
// via http://www.plunk.org/~hatch/rightway.php
    template<typename T>
    inline float AngleBetween(const Vector3<T> &v1, const Vector3<T> &v2) {
        if (Dot(v1, v2) < 0)
            return Pi - 2 * glm::asin(Length(v1 + v2) / 2);
        else
            return 2 * glm::asin(Length(v2 - v1) / 2);
    }

    template<typename T>
    inline T AbsDot(const Vector3<T> &v1, const Vector3<T> &v2) {
        DCHECK(!v1.HasNaN() && !v2.HasNaN());
        return std::abs(Dot(v1, v2));
    }

    template<typename T>
    inline float AngleBetween(const Normal3<T> &a, const Normal3<T> &b) {
        if (Dot(a, b) < 0)
            return Pi - 2 * glm::asin(Length(a + b) / 2);
        else
            return 2 * glm::asin(Length(b - a) / 2);
    }

    template<typename T>
    inline Vector3<T> GramSchmidt(const Vector3<T> &a, const Vector3<T> &b) {
        return a - Dot(a, b) * b;
    }

    template<typename T>
    inline void CoordinateSystem(const Vector3<T> &v1, Vector3<T> *v2,
                                 Vector3<T> *v3) {
        float sign = std::copysign(float(1), v1.z);
        float a = -1 / (sign + v1.z);
        float b = v1.x * v1.y * a;
        *v2 = Vector3<T>(1 + sign * v1.x * v1.x * a, sign * b, -sign * v1.x);
        *v3 = Vector3<T>(b, sign + v1.y * v1.y * a, -v1.y);
    }

    template<typename T>
    inline void CoordinateSystem(const Normal3<T> &v1, Vector3<T> *v2,
                                 Vector3<T> *v3) {
        float sign = std::copysign(float(1), v1.z);
        float a = -1 / (sign + v1.z);
        float b = v1.x * v1.y * a;
        *v2 = Vector3<T>(1 + sign * v1.x * v1.x * a, sign * b, -sign * v1.x);
        *v3 = Vector3<T>(b, sign + v1.y * v1.y * a, -v1.y);
    }

#pragma endregion Vector3 Inline Functions

}

#endif //JADEHARE_CORE_MATH_VECTOR_H
