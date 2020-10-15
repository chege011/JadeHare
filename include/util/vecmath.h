//
// Created by chege on 2020/10/5.
//

#ifndef JADEHARE_UTIL_VECMATH_H
#define JADEHARE_UTIL_VECMATH_H

#include <jadehare.h>
#include <util/check.h>
#include <util/float.h>
#include <util/math.h>

namespace {
    inline float FMA(float a, float b, float c) {
        return std::fma(a, b, c);
    }

    inline double FMA(double a, double b, double c) {
        return std::fma(a, b, c);
    }
}

namespace jadehare {
    // Tuple2 Definition
    template<template<typename> class Child, typename T>
    class Tuple2 : public glm::vec<2, T, glm::defaultp> {
    public:
        // Tuple2 Public Methods
        using glm::vec<2, T, glm::defaultp>::x;
        using glm::vec<2, T, glm::defaultp>::y;

        using glm::vec<2, T, glm::defaultp>::operator*=;
        using glm::vec<2, T, glm::defaultp>::operator/=;
        using glm::vec<2, T, glm::defaultp>::operator[];

        static const int nDimensions = 2;

        Tuple2() = default;

        Tuple2(T x, T y) : glm::vec<2, T, glm::defaultp>{x, y} { DCHECK(!HasNaN()); }

        [[nodiscard]] bool HasNaN() const { return IsNaN(x) || IsNaN(y); }

#ifndef NDEBUG
        // The default versions of these are fine for release builds; for debug
        // we define them so that we can add the Assert checks.

        Tuple2(const Child<T> &c) {
            DCHECK(!c.HasNaN());
            x = c.x;
            y = c.y;
        }

        Child<T> &operator=(const Child<T> &c) {
            DCHECK(!c.HasNaN());
            x = c.x;
            y = c.y;
            return static_cast<Child<T> &>(*this);
        }

#endif  // !NDEBUG

        template<typename U>
        auto operator+(const Child<U> &c) const -> Child<decltype(T{} + U{})> {
            DCHECK(!c.HasNaN());
            return {x + c.x, y + c.y};
        }

        template<typename U>
        Child<T> &operator+=(const Child<U> &c) {
            DCHECK(!c.HasNaN());
            x += c.x;
            y += c.y;
            return static_cast<Child<T> &>(*this);
        }

        template<typename U>
        auto operator-(const Child<U> &c) const -> Child<decltype(T{} - U{})> {
            DCHECK(!c.HasNaN());
            return {x - c.x, y - c.y};
        }

        template<typename U>
        Child<T> &operator-=(const Child<U> &c) {
            DCHECK(!c.HasNaN());
            x -= c.x;
            y -= c.y;
            return static_cast<Child<T> &>(*this);
        }


        bool operator==(const Child<T> &c) const { return x == c.x && y == c.y; }

        bool operator!=(const Child<T> &c) const { return x != c.x || y != c.y; }

        template<typename U>
        auto operator*(U s) const -> Child<decltype(T{} * U{})> {
            return {s * x, s * y};
        }

//        template <typename U>
//         Child<T> &operator*=(U s) {
//            DCHECK(!IsNaN(s));
//            x *= s;
//            y *= s;
//            return static_cast<Child<T> &>(*this);
//        }

        template<typename U>
        auto operator/(U d) const -> Child<decltype(T{} / U{})> {
            DCHECK(d != 0 && !IsNaN(d));
            return {x / d, y / d};
        }

//        template <typename U>
//         Child<T> &operator/=(U d) {
//            DCHECK_NE(d, 0);
//            DCHECK(!IsNaN(d));
//            x /= d;
//            y /= d;
//            return static_cast<Child<T> &>(*this);
//        }


        Child<T> operator-() const { return {-x, -y}; }
    };

    // Tuple2 Inline Functions
#pragma region Tuple2 Inline Functions

    template<template<class> class C, typename T, typename U>
    inline auto operator*(U s, const Tuple2<C, T> &t) -> C<decltype(T{} * U{})> {
        DCHECK(!t.HasNaN());
        return t * s;
    }

    template<template<class> class C, typename T>
    inline C<T> Abs(const Tuple2<C, T> &t) {
        // "argument-dependent lookup..." (here and elsewhere)
        using std::abs;
        return {abs(t.x), abs(t.y)};
    }

    template<template<class> class C, typename T>
    inline C<T> Ceil(const Tuple2<C, T> &t) {
        using std::ceil;
        return {ceil(t.x), ceil(t.y)};
    }

    template<template<class> class C, typename T>
    inline C<T> Floor(const Tuple2<C, T> &t) {
        using std::floor;
        return {floor(t.x), floor(t.y)};
    }

    template<template<class> class C, typename T>
    inline auto Lerp(float t, const Tuple2<C, T> &t0, const Tuple2<C, T> &t1) {
        return (1 - t) * t0 + t * t1;
    }

    template<template<class> class C, typename T>
    inline C<T> FMA(float a, const Tuple2<C, T> &b, const Tuple2<C, T> &c) {
        return {FMA(a, b.x, c.x), FMA(a, b.y, c.y)};
    }

    template<template<class> class C, typename T>
    inline C<T> FMA(const Tuple2<C, T> &a, float b, const Tuple2<C, T> &c) {
        return FMA(b, a, c);
    }

    template<template<class> class C, typename T>
    inline C<T> Min(const Tuple2<C, T> &t0, const Tuple2<C, T> &t1) {
        using std::min;
        return {min(t0.x, t1.x), min(t0.y, t1.y)};
    }

    template<template<class> class C, typename T>
    inline T MinComponentValue(const Tuple2<C, T> &t) {
        using std::min;
        return min({t.x, t.y});
    }

    template<template<class> class C, typename T>
    inline int MinComponentIndex(const Tuple2<C, T> &t) {
        return (t.x < t.y) ? 0 : 1;
    }

    template<template<class> class C, typename T>
    inline C<T> Max(const Tuple2<C, T> &t0, const Tuple2<C, T> &t1) {
        using std::max;
        return {max(t0.x, t1.x), max(t0.y, t1.y)};
    }

    template<template<class> class C, typename T>
    inline T MaxComponentValue(const Tuple2<C, T> &t) {
        using std::max;
        return max({t.x, t.y});
    }

    template<template<class> class C, typename T>
    inline int MaxComponentIndex(const Tuple2<C, T> &t) {
        return (t.x > t.y) ? 0 : 1;
    }

//    template<template<class> class C, typename T>
//     inline C<T> Permute(const Tuple2<C, T> &t, pstd::array<int, 2> p)
//    {
//        return {t[p[0]], t[p[1]]};
//    }

    template<template<class> class C, typename T>
    inline T HProd(const Tuple2<C, T> &t) {
        return t.x * t.y;
    }

#pragma endregion Tuple2 Inline Functions

    // Tuple3 Definition
    template<template<typename> class Child, typename T>
    class Tuple3 : public glm::vec<3, T, glm::defaultp> {
    public:
        static const int nDimensions = 3;

        // Tuple3 Public Methods
        using glm::vec<3, T, glm::defaultp>::x;
        using glm::vec<3, T, glm::defaultp>::y;
        using glm::vec<3, T, glm::defaultp>::z;

        using glm::vec<3, T, glm::defaultp>::operator*=;
        using glm::vec<3, T, glm::defaultp>::operator/=;
        using glm::vec<3, T, glm::defaultp>::operator[];

        Tuple3() = default;

        Tuple3(T x, T y, T z) : glm::vec<3, T, glm::defaultp>{x, y, z} { DCHECK(!HasNaN()); }

        [[nodiscard]] bool HasNaN() const { return IsNaN(x) || IsNaN(y) || IsNaN(z); }


//        T operator[](int i) const {
//            DCHECK(i >= 0 && i <= 2);
//            if (i == 0)
//                return x;
//            if (i == 1)
//                return y;
//            return z;
//        }
//
//
//        T &operator[](int i) {
//            DCHECK(i >= 0 && i <= 2);
//            if (i == 0)
//                return x;
//            if (i == 1)
//                return y;
//            return z;
//        }

        template<typename U>
        auto operator+(const Child<U> &c) const -> Child<decltype(T{} + U{})> {
            DCHECK(!c.HasNaN());
            return {x + c.x, y + c.y, z + c.z};
        }

#ifndef NDEBUG
        // The default versions of these are fine for release builds; for debug
        // we define them so that we can add the Assert checks.

        Tuple3(const Child<T> &c) {
            DCHECK(!c.HasNaN());
            x = c.x;
            y = c.y;
            z = c.z;
        }


        Child<T> &operator=(const Child<T> &c) {
            DCHECK(!c.HasNaN());
            x = c.x;
            y = c.y;
            z = c.z;
            return static_cast<Child<T> &>(*this);
        }

#endif  // !NDEBUG

        template<typename U>
        Child<T> &operator+=(const Child<U> &c) {
            DCHECK(!c.HasNaN());
            x += c.x;
            y += c.y;
            z += c.z;
            return static_cast<Child<T> &>(*this);
        }

        template<typename U>
        auto operator-(const Child<U> &c) const -> Child<decltype(T{} - U{})> {
            DCHECK(!c.HasNaN());
            return {x - c.x, y - c.y, z - c.z};
        }

        template<typename U>
        Child<T> &operator-=(const Child<U> &c) {
            DCHECK(!c.HasNaN());
            x -= c.x;
            y -= c.y;
            z -= c.z;
            return static_cast<Child<T> &>(*this);
        }


        bool operator==(const Child<T> &c) const { return x == c.x && y == c.y && z == c.z; }

        bool operator!=(const Child<T> &c) const { return x != c.x || y != c.y || z != c.z; }

        template<typename U>
        auto operator*(U s) const -> Child<decltype(T{} * U{})> {
            return {s * x, s * y, s * z};
        }

//        template <typename U>
//         Child<T> &operator*=(U s) {
//            DCHECK(!IsNaN(s));
//            x *= s;
//            y *= s;
//            z *= s;
//            return static_cast<Child<T> &>(*this);
//        }

        template<typename U>
        auto operator/(U d) const -> Child<decltype(T{} / U{})> {
            DCHECK_NE(d, 0);
            return {x / d, y / d, z / d};
        }
//        template <typename U>
//         Child<T> &operator/=(U d) {
//            DCHECK_NE(d, 0);
//            x /= d;
//            y /= d;
//            z /= d;
//            return static_cast<Child<T> &>(*this);
//        }

        Child<T> operator-() const { return {-x, -y, -z}; }
    };

    // Tuple3 Inline Functions
#pragma region Tuple3 Inline Functions

    template<template<class> class C, typename T, typename U>
    inline auto operator*(U s, const Tuple3<C, T> &t) -> C<decltype(T{} * U{})> {
        return t * s;
    }

    template<template<class> class C, typename T>
    inline C<T> Abs(const Tuple3<C, T> &t) {
        using std::abs;
        return {abs(t.x), abs(t.y), abs(t.z)};
    }

    template<template<class> class C, typename T>
    inline C<T> Ceil(const Tuple3<C, T> &t) {
        using std::ceil;
        return {ceil(t.x), ceil(t.y), ceil(t.z)};
    }

    template<template<class> class C, typename T>
    inline C<T> Floor(const Tuple3<C, T> &t) {
        using std::floor;
        return {floor(t.x), floor(t.y), floor(t.z)};
    }

    template<template<class> class C, typename T>
    inline auto Lerp(float t, const Tuple3<C, T> &t0, const Tuple3<C, T> &t1) {
        return (1 - t) * t0 + t * t1;
    }

    template<template<class> class C, typename T>
    inline C<T> FMA(float a, const Tuple3<C, T> &b, const Tuple3<C, T> &c) {
        return {FMA(a, b.x, c.x), FMA(a, b.y, c.y), FMA(a, b.z, c.z)};
    }

    template<template<class> class C, typename T>
    inline C<T> FMA(const Tuple3<C, T> &a, float b, const Tuple3<C, T> &c) {
        return FMA(b, a, c);
    }

    template<template<class> class C, typename T>
    inline C<T> Min(const Tuple3<C, T> &t1, const Tuple3<C, T> &t2) {
        using std::min;
        return {min(t1.x, t2.x), min(t1.y, t2.y), min(t1.z, t2.z)};
    }

    template<template<class> class C, typename T>
    inline T MinComponentValue(const Tuple3<C, T> &t) {
        using std::min;
        return min({t.x, t.y, t.z});
    }

    template<template<class> class C, typename T>
    inline int MinComponentIndex(const Tuple3<C, T> &t) {
        return (t.x < t.y) ? ((t.x < t.z) ? 0 : 2) : ((t.y < t.z) ? 1 : 2);
    }

    template<template<class> class C, typename T>
    inline C<T> Max(const Tuple3<C, T> &t1, const Tuple3<C, T> &t2) {
        using std::max;
        return {max(t1.x, t2.x), max(t1.y, t2.y), max(t1.z, t2.z)};
    }

    template<template<class> class C, typename T>
    inline T MaxComponentValue(const Tuple3<C, T> &t) {
        using std::max;
        return max({t.x, t.y, t.z});
    }

    template<template<class> class C, typename T>
    inline int MaxComponentIndex(const Tuple3<C, T> &t) {
        return (t.x > t.y) ? ((t.x > t.z) ? 0 : 2) : ((t.y > t.z) ? 1 : 2);
    }

//    template<template<class> class C, typename T>
//     inline C<T> Permute(const Tuple3<C, T> &t, pstd::array<int, 3> p)
//    {
//        return {t[p[0]], t[p[1]], t[p[2]]};
//    }

    template<template<class> class C, typename T>
    inline T HProd(const Tuple3<C, T> &t) {
        return t.x * t.y * t.z;
    }

#pragma endregion Tuple3 Inline Functions

#pragma region Vector

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

#pragma endregion Vector

#pragma region Point

    // Point2 Definition
    template<typename T>
    class Point2 : public Tuple2<Point2, T> {
    public:
        // Point2 Public Methods
        using Tuple2<Point2, T>::x;
        using Tuple2<Point2, T>::y;
        using Tuple2<Point2, T>::HasNaN;
        using Tuple2<Point2, T>::operator+;
        using Tuple2<Point2, T>::operator+=;
        using Tuple2<Point2, T>::operator*;
        using Tuple2<Point2, T>::operator*=;


        Point2() { x = y = 0; }


        Point2(T x, T y) : Tuple2<Point2, T>(x, y) {}

        template<typename U>
        explicit Point2(const Point2<U> &v)
                : Tuple2<Point2, T>(T(v.x), T(v.y)) {}

        template<typename U>
        explicit Point2(const Vector2<U> &v)
                : Tuple2<Point2, T>(T(v.x), T(v.y)) {}

        template<typename U>
        auto operator+(const Vector2<U> &v) const
        -> Point2<decltype(T{} + U{})> {
            DCHECK(!v.HasNaN());
            return {x + v.x, y + v.y};
        }

        template<typename U>
        Point2<T> &operator+=(const Vector2<U> &v) {
            DCHECK(!v.HasNaN());
            x += v.x;
            y += v.y;
            return *this;
        }

        // We can't do using operator- above, since we don't want to pull in
        // the Point-Point -> Point one so that we can return a vector
        // instead...
        template<typename U>
        auto operator-(const Point2<U> &p) const
        -> Vector2<decltype(T{} - U{})> {
            DCHECK(!p.HasNaN());
            return {x - p.x, y - p.y};
        }

        template<typename U>
        auto operator-(const Vector2<U> &v) const
        -> Point2<decltype(T{} - U{})> {
            DCHECK(!v.HasNaN());
            return {x - v.x, y - v.y};
        }

        template<typename U>
        Point2<T> &operator-=(const Vector2<U> &v) {
            DCHECK(!v.HasNaN());
            x -= v.x;
            y -= v.y;
            return *this;
        }
    };

    // Point3 Definition
    template<typename T>
    class Point3 : public Tuple3<Point3, T> {
    public:
        // Point3 Public Methods
        using Tuple3<Point3, T>::x;
        using Tuple3<Point3, T>::y;
        using Tuple3<Point3, T>::z;
        using Tuple3<Point3, T>::HasNaN;
        using Tuple3<Point3, T>::operator+;
        using Tuple3<Point3, T>::operator+=;
        using Tuple3<Point3, T>::operator*;
        using Tuple3<Point3, T>::operator*=;
        using Tuple3<Point3, T>::operator-;

        Point3() = default;


        Point3(T x, T y, T z) : Tuple3<Point3, T>(x, y, z) {}

        template<typename U>
        explicit Point3(const Point3<U> &p)
                : Tuple3<Point3, T>(T(p.x), T(p.y), T(p.z)) {}

        template<typename U>
        explicit Point3(const Vector3<U> &v)
                : Tuple3<Point3, T>(T(v.x), T(v.y), T(v.z)) {}

        template<typename U>
        auto operator+(const Vector3<U> &v) const

        -> Point3<decltype(T{} + U{})> {
            DCHECK(!v.HasNaN());
            return {x + v.x, y + v.y, z + v.z};
        }

        template<typename U>
        Point3<T> &operator+=(const Vector3<U> &v) {
            DCHECK(!v.HasNaN());
            x += v.x;
            y += v.y;
            z += v.z;
            return *this;
        }

        template<typename U>
        auto operator-(const Vector3<U> &v) const
        -> Point3<decltype(T{} - U{})> {
            DCHECK(!v.HasNaN());
            return {x - v.x, y - v.y, z - v.z};
        }

        template<typename U>
        Point3<T> &operator-=(const Vector3<U> &v) {
            DCHECK(!v.HasNaN());
            x -= v.x;
            y -= v.y;
            z -= v.z;
            return *this;
        }

        // We can't do using operator- above, since we don't want to pull in
        // the Point-Point -> Point one so that we can return a vector
        // instead...
        template<typename U>
        auto operator-(const Point3<U> &p) const
        -> Vector3<decltype(T{} - U{})> {
            DCHECK(!p.HasNaN());
            return {x - p.x, y - p.y, z - p.z};
        }
    };

// Point2* Definitions
    using Point2f = Point2<float>;
    using Point2i = Point2<int>;

// Point3* Definitions
    using Point3f = Point3<float>;
    using Point3i = Point3<int>;
#pragma endregion Point

#pragma region Normal

    // Normal3 Definition
    template<typename T>
    class Normal3 : public Tuple3<Normal3, T> {
    public:
        // Normal3 Public Methods
        using Tuple3<Normal3, T>::x;
        using Tuple3<Normal3, T>::y;
        using Tuple3<Normal3, T>::z;
        using Tuple3<Normal3, T>::HasNaN;
        using Tuple3<Normal3, T>::operator+;
        using Tuple3<Normal3, T>::operator*;
        using Tuple3<Normal3, T>::operator*=;

        Normal3() = default;


        Normal3(T x, T y, T z) : Tuple3<Normal3, T>(x, y, z) {}

        template<typename U>
        explicit Normal3<T>(const Normal3<U> &v)
                : Tuple3<Normal3, T>(T(v.x), T(v.y), T(v.z)) {}

        template<typename U>
        explicit Normal3<T>(const Vector3<U> &v)
                : Tuple3<Normal3, T>(T(v.x), T(v.y), T(v.z)) {}
    };

    using Normal3f = Normal3<float>;
#pragma endregion Normal

#pragma region Quaternion

    // Quaternion Definition
    class Quaternion : public glm::quat {
    public:
        // Quaternion Public Methods
        Quaternion() = default;

        Quaternion(float w, float x, float y, float z) : glm::quat(w, x, y, z) {}

        using glm::quat::operator+=;
        using glm::quat::operator-=;
        using glm::quat::operator*=;
        using glm::quat::operator/=;

        Quaternion operator+(const Quaternion &q) const { return {w + q.w, x + q.x, y + q.y, z + q.z}; }

//        Quaternion &operator-=(const Quaternion &q) {
//            v -= q.v;
//            w -= q.w;
//            return *this;
//        }

        Quaternion operator-() const { return {-w, -x, -y, -z}; }

        Quaternion operator-(const Quaternion &q) const { return {w - q.w, x - q.x, y - q.y, z - q.z}; }


//        Quaternion &operator*=(float f)
//        {
//            x *= f;
//            y *= f;
//            z *= f;
//            w *= f;
//            return *this;
//        }
//
//
        Quaternion operator*(float f) const { return {w * f, x * f, y * f, z * f};}

//        Quaternion &operator/=(float f) {
//            DCHECK_NE(0, f);
//            v /= f;
//            w /= f;
//            return *this;
//        }

        Quaternion operator/(float f) const {
            DCHECK_NE(0, f);
            return {w / f, x / f, y / f, z / f};
        }

//        std::string ToString() const;

        // Quaternion Public Members
        using glm::quat::x;
        using glm::quat::y;
        using glm::quat::z;
        using glm::quat::w;
    };

#pragma endregion Quaternion

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


#endif //JADEHARE_UTIL_VECMATH_H
