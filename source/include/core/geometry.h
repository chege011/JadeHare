//
// Created by 1129 on 2020/9/24.
//

#if defined(_MSC_VER)
#define NOMINMAX
#pragma once
#endif

#ifndef JADEHARE_CORE_GEOMETRY_H
#define JADEHARE_CORE_GEOMETRY_H

#include "jadehare.h"
#include "medium.h"

namespace jadehare
{
    typedef glm::vec2 Vector2f;
    typedef glm::ivec2 Vector2i;
    typedef glm::vec3 Vector3f;
    typedef glm::ivec3 Vector3i;

    typedef glm::vec2 Point2f;
    typedef glm::ivec2 Point2i;
    typedef glm::vec3 Point3f;
    typedef glm::ivec3 Point3i;

    typedef glm::vec3 Normal3f;

    inline std::ostream &operator<<(std::ostream &os, const glm::vec2 &v)
    {
        os << "[ " << v.x << ", " << v.y << " ]";
        return os;
    }

    inline std::ostream &operator<<(std::ostream &os, const glm::vec3 &v)
    {
        os << "[ " << v.x << ", " << v.y << ", " << v.z << " ]";
        return os;
    }

    template<typename T, typename V, typename P>
    class Bounds2
    {
    public:
        // Bounds2 Public Methods
        Bounds2()
        {
            T minNum = std::numeric_limits<T>::lowest();
            T maxNum = std::numeric_limits<T>::max();
            pMin = P(maxNum, maxNum);
            pMax = P(minNum, minNum);
        }

        explicit Bounds2(const P &p) : pMin(p), pMax(p) {}

        Bounds2(const P &p1, const P &p2)
        {
            pMin = P(std::min(p1.x, p2.x), std::min(p1.y, p2.y));
            pMax = P(std::max(p1.x, p2.x), std::max(p1.y, p2.y));
        }

//        template<typename U>
//        explicit operator Bounds2<U>() const
//        {
//            return Bounds2<U>((Point2<U>) pMin, (Point2<U>) pMax);
//        }

        V Diagonal() const { return pMax - pMin; }

        T Area() const
        {
            V d = pMax - pMin;
            return (d.x * d.y);
        }

        int MaximumExtent() const
        {
            V diag = Diagonal();
            if (diag.x > diag.y)
                return 0;
            else
                return 1;
        }

        inline const P &operator[](int i) const
        {
            assert(i == 0 || i == 1);
            return (i == 0) ? pMin : pMax;
        }

        inline P &operator[](int i)
        {
            assert(i == 0 || i == 1);
            return (i == 0) ? pMin : pMax;
        }

        bool operator==(const Bounds2<T,V,P> &b) const
        {
            return b.pMin == pMin && b.pMax == pMax;
        }

        bool operator!=(const Bounds2<T,V,P> &b) const
        {
            return b.pMin != pMin || b.pMax != pMax;
        }

//        Point2f Lerp(const Point2f &t) const
//        {
//            return Point2f(pbrt::Lerp(t.x, pMin.x, pMax.x),
//                             pbrt::Lerp(t.y, pMin.y, pMax.y));
//        }

        V Offset(const P &p) const
        {
            V o = p - pMin;
            if (pMax.x > pMin.x) o.x /= pMax.x - pMin.x;
            if (pMax.y > pMin.y) o.y /= pMax.y - pMin.y;
            return o;
        }

//        void BoundingSphere(Point2f *c, float *rad) const
//        {
//            *c = (pMin + pMax) / 2;
//            *rad = Inside(*c, *this) ? Distance(*c, pMax) : 0;
//        }

        // Bounds2 Public Data
        P pMin, pMax;
    };

    template<typename T, typename V, typename P>
    class Bounds3
    {
    public:
        // Bounds3 Public Methods
        Bounds3()
        {
            T minNum = std::numeric_limits<T>::lowest();
            T maxNum = std::numeric_limits<T>::max();
            pMin = P(maxNum, maxNum, maxNum);
            pMax = P(minNum, minNum, minNum);
        }

        explicit Bounds3(const P &p) : pMin(p), pMax(p) {}

        Bounds3(const P &p1, const P &p2)
                : pMin(std::min(p1.x, p2.x), std::min(p1.y, p2.y),
                       std::min(p1.z, p2.z)),
                  pMax(std::max(p1.x, p2.x), std::max(p1.y, p2.y),
                       std::max(p1.z, p2.z)) {}

        bool operator==(const Bounds3<T,V,P> &b) const
        {
            return b.pMin == pMin && b.pMax == pMax;
        }

        bool operator!=(const Bounds3<T,V,P> &b) const
        {
            return b.pMin != pMin || b.pMax != pMax;
        }

        P Corner(int corner) const
        {
            assert(corner >= 0 && corner < 8);
            return P((*this)[(corner & 1)].x,
                             (*this)[(corner & 2) ? 1 : 0].y,
                             (*this)[(corner & 4) ? 1 : 0].z);
        }

        V Diagonal() const { return pMax - pMin; }

        T SurfaceArea() const
        {
            V d = Diagonal();
            return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
        }

        T Volume() const
        {
            V d = Diagonal();
            return d.x * d.y * d.z;
        }

        int MaximumExtent() const
        {
            V d = Diagonal();
            if (d.x > d.y && d.x > d.z)
                return 0;
            else if (d.y > d.z)
                return 1;
            else
                return 2;
        }

//        P Lerp(const Point3f &t) const
//        {
//            return Point3<T>(pbrt::Lerp(t.x, pMin.x, pMax.x),
//                             pbrt::Lerp(t.y, pMin.y, pMax.y),
//                             pbrt::Lerp(t.z, pMin.z, pMax.z));
//        }

        V Offset(const P &p) const
        {
            V o = p - pMin;
            if (pMax.x > pMin.x) o.x /= pMax.x - pMin.x;
            if (pMax.y > pMin.y) o.y /= pMax.y - pMin.y;
            if (pMax.z > pMin.z) o.z /= pMax.z - pMin.z;
            return o;
        }

        void BoundingSphere(P *center, float *radius) const
        {
            *center = (pMin + pMax) / 2;
            *radius = Inside(*center, *this) ? Distance(*center, pMax) : 0;
        }

//        bool IntersectP(const Ray &ray, float *hitt0 = nullptr,
//                        float *hitt1 = nullptr) const;
//
//        inline bool IntersectP(const Ray &ray, const Vector3f &invDir,
//                               const int dirIsNeg[3]) const;

        // Bounds3 Public Data
        P pMin, pMax;
    };

    typedef Bounds2<float, Vector2f, Point2f> Bounds2f;
    typedef Bounds2<int, Vector2i, Point2i> Bounds2i;
    typedef Bounds3<float, Vector3f, Point3f> Bounds3f;
    typedef Bounds3<int, Vector3i, Point3i> Bounds3i;
}

#endif //JADEHARE_CORE_GEOMETRY_H
