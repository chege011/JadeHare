//
// Created by 1129 on 2020/10/16.
//

#ifndef JADEHARE_CORE_MATH_TUPLE_H
#define JADEHARE_CORE_MATH_TUPLE_H

#include "jadehare.h"
#include "util/check.h"

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


#pragma region Tuple2 Inline Functions

// Tuple2 Inline Functions
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


#pragma region Tuple3 Inline Functions

// Tuple3 Inline Functions
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
}
#endif //JADEHARE_CORE_MATH_TUPLE_H
