//
// Created by 1129 on 2020/10/16.
//

#ifndef JADEHARE_CORE_MATH_BOUNDS_H
#define JADEHARE_CORE_MATH_BOUNDS_H

#include "jadehare.h"
#include "mathematics.h"
#include "vector.h"
#include "point.h"

namespace jadehare {

#pragma region Bounds

// Bounds2 Definition
    template<typename T>
    class Bounds2 {
    public:
        // Bounds2 Public Methods

        Bounds2() {
            T minNum = std::numeric_limits<T>::lowest();
            T maxNum = std::numeric_limits<T>::max();
            pMin = Point2<T>(maxNum, maxNum);
            pMax = Point2<T>(minNum, minNum);
        }

        explicit Bounds2(const Point2<T> &p) : pMin(p), pMax(p) {}

        Bounds2(const Point2<T> &p1, const Point2<T> &p2)
                : pMin(Min(p1, p2)), pMax(Max(p1, p2)) {}

        template<typename U>
        explicit Bounds2(const Bounds2<U> &b) {
            if (b.IsEmpty())
                // Be careful about overflowing float->int conversions and the
                // like.
                *this = Bounds2<T>();
            else {
                pMin = Point2<T>(b.pMin);
                pMax = Point2<T>(b.pMax);
            }
        }


        Vector2<T> Diagonal() const { return pMax - pMin; }


        T Area() const {
            Vector2<T> d = pMax - pMin;
            return d.x * d.y;
        }


        bool IsEmpty() const { return pMin.x >= pMax.x || pMin.y >= pMax.y; }


        bool IsDegenerate() const { return pMin.x > pMax.x || pMin.y > pMax.y; }


        int MaxDimension() const {
            Vector2<T> diag = Diagonal();
            if (diag.x > diag.y)
                return 0;
            else
                return 1;
        }

        const Point2<T> &operator[](int i) const {
            DCHECK(i == 0 || i == 1);
            return (i == 0) ? pMin : pMax;
        }

        Point2<T> &operator[](int i) {
            DCHECK(i == 0 || i == 1);
            return (i == 0) ? pMin : pMax;
        }

        bool operator==(const Bounds2<T> &b) const {
            return b.pMin == pMin && b.pMax == pMax;
        }

        bool operator!=(const Bounds2<T> &b) const {
            return b.pMin != pMin || b.pMax != pMax;
        }

        Point2<T> Corner(int corner) const {
            DCHECK(corner >= 0 && corner < 4);
            return Point2<T>((*this)[(corner & 1)].x, (*this)[(corner & 2) ? 1 : 0].y);
        }

        Point2<T> Lerp(const Point2f &t) const {
            return Point2<T>(jadehare::Lerp(t.x, pMin.x, pMax.x),
                             jadehare::Lerp(t.y, pMin.y, pMax.y));
        }

        Vector2<T> Offset(const Point2<T> &p) const {
            Vector2<T> o = p - pMin;
            if (pMax.x > pMin.x)
                o.x /= pMax.x - pMin.x;
            if (pMax.y > pMin.y)
                o.y /= pMax.y - pMin.y;
            return o;
        }

        void BoundingSphere(Point2<T> *c, float *rad) const {
            *c = (pMin + pMax) / 2;
            *rad = Inside(*c, *this) ? Distance(*c, pMax) : 0;
        }

//        std::string ToString() const { return StringPrintf("[ %s - %s ]", pMin, pMax); }

        // Bounds2 Public Members
        Point2<T> pMin, pMax;
    };

    // Bounds3 Definition
    template<typename T>
    class Bounds3 {
    public:
        // Bounds3 Public Methods

        Bounds3() {
            T minNum = std::numeric_limits<T>::lowest();
            T maxNum = std::numeric_limits<T>::max();
            pMin = Point3<T>(maxNum, maxNum, maxNum);
            pMax = Point3<T>(minNum, minNum, minNum);
        }


        explicit Bounds3(const Point3<T> &p) : pMin(p), pMax(p) {}


        Bounds3(const Point3<T> &p1, const Point3<T> &p2)
                : pMin(Min(p1, p2)), pMax(Max(p1, p2)) {}


        const Point3<T> &operator[](int i) const {
            DCHECK(i == 0 || i == 1);
            return (i == 0) ? pMin : pMax;
        }

        Point3<T> &operator[](int i) {
            DCHECK(i == 0 || i == 1);
            return (i == 0) ? pMin : pMax;
        }


        Point3<T> Corner(int corner) const {
            DCHECK(corner >= 0 && corner < 8);
            return Point3<T>((*this)[(corner & 1)].x, (*this)[(corner & 2) ? 1 : 0].y,
                             (*this)[(corner & 4) ? 1 : 0].z);
        }


        Vector3<T> Diagonal() const { return pMax - pMin; }


        T SurfaceArea() const {
            Vector3<T> d = Diagonal();
            return 2 * (d.x * d.y + d.x * d.z + d.y * d.z);
        }


        T Volume() const {
            Vector3<T> d = Diagonal();
            return d.x * d.y * d.z;
        }


        int MaxDimension() const {
            Vector3<T> d = Diagonal();
            if (d.x > d.y && d.x > d.z)
                return 0;
            else if (d.y > d.z)
                return 1;
            else
                return 2;
        }


        Point3<T> Lerp(const Point3f &t) const {
            return Point3<T>(jadehare::Lerp(t.x, pMin.x, pMax.x), jadehare::Lerp(t.y, pMin.y, pMax.y),
                             jadehare::Lerp(t.z, pMin.z, pMax.z));
        }


        Vector3<T> Offset(const Point3<T> &p) const {
            Vector3<T> o = p - pMin;
            if (pMax.x > pMin.x)
                o.x /= pMax.x - pMin.x;
            if (pMax.y > pMin.y)
                o.y /= pMax.y - pMin.y;
            if (pMax.z > pMin.z)
                o.z /= pMax.z - pMin.z;
            return o;
        }


        void BoundingSphere(Point3<T> *center, float *radius) const {
            *center = (pMin + pMax) / 2;
            *radius = Inside(*center, *this) ? Distance(*center, pMax) : 0;
        }


        bool IsEmpty() const {
            return pMin.x >= pMax.x || pMin.y >= pMax.y || pMin.z >= pMax.z;
        }

        bool IsDegenerate() const {
            return pMin.x > pMax.x || pMin.y > pMax.y || pMin.z > pMax.z;
        }

        template<typename U>
        explicit Bounds3(const Bounds3<U> &b) {
            if (b.IsEmpty())
                // Be careful about overflowing float->int conversions and the
                // like.
                *this = Bounds3<T>();
            else {
                pMin = Point3<T>(b.pMin);
                pMax = Point3<T>(b.pMax);
            }
        }

        bool operator==(const Bounds3<T> &b) const {
            return b.pMin == pMin && b.pMax == pMax;
        }

        bool operator!=(const Bounds3<T> &b) const {
            return b.pMin != pMin || b.pMax != pMax;
        }

        bool IntersectP(const Point3f &o, const Vector3f &d, float tMax = Infinity,
                        float *hitt0 = nullptr, float *hitt1 = nullptr) const;

        bool IntersectP(const Point3f &o, const Vector3f &d, float tMax,
                        const Vector3f &invDir, const int dirIsNeg[3]) const;

//        std::string ToString() const { return StringPrintf("[ %s - %s ]", pMin, pMax); }

        // Bounds3 Public Members
        Point3<T> pMin, pMax;
    };

    // Bounds[23][fi] Definitions
    using Bounds2f = Bounds2<float>;
    using Bounds2i = Bounds2<int>;
    using Bounds3f = Bounds3<float>;
    using Bounds3i = Bounds3<int>;
#pragma endregion Bounds

#pragma region Bounds2 Inline Functions

    // Bounds2 Inline Functions
    template<typename T>
    inline Bounds2<T> Union(const Bounds2<T> &b, const Point2<T> &p) {
        // Be careful to not run the two-point Bounds constructor.
        Bounds2<T> ret;
        ret.pMin = Min(b.pMin, p);
        ret.pMax = Max(b.pMax, p);
        return ret;
    }

    template<typename T>
    inline Bounds2<T> Union(const Bounds2<T> &b1, const Bounds2<T> &b2) {
        // Be careful to not run the two-point Bounds constructor.
        Bounds2<T> ret;
        ret.pMin = Min(b1.pMin, b2.pMin);
        ret.pMax = Max(b1.pMax, b2.pMax);
        return ret;
    }

    template<typename T>
    inline Bounds2<T> Intersect(const Bounds2<T> &b1, const Bounds2<T> &b2) {
        // Be careful to not run the two-point Bounds constructor.
        Bounds2<T> b;
        b.pMin = Max(b1.pMin, b2.pMin);
        b.pMax = Min(b1.pMax, b2.pMax);
        return b;
    }

    template<typename T>
    inline bool Overlaps(const Bounds2<T> &ba, const Bounds2<T> &bb) {
        bool x = (ba.pMax.x >= bb.pMin.x) && (ba.pMin.x <= bb.pMax.x);
        bool y = (ba.pMax.y >= bb.pMin.y) && (ba.pMin.y <= bb.pMax.y);
        return (x && y);
    }

    template<typename T>
    inline bool Inside(const Point2<T> &pt, const Bounds2<T> &b) {
        return (pt.x >= b.pMin.x && pt.x <= b.pMax.x && pt.y >= b.pMin.y && pt.y <= b.pMax.y);
    }

    template<typename T>
    inline bool Inside(const Bounds2<T> &ba, const Bounds2<T> &bb) {
        return (ba.pMin.x >= bb.pMin.x && ba.pMax.x <= bb.pMax.x && ba.pMin.y >= bb.pMin.y &&
                ba.pMax.y <= bb.pMax.y);
    }

    template<typename T>
    inline bool InsideExclusive(const Point2<T> &pt, const Bounds2<T> &b) {
        return (pt.x >= b.pMin.x && pt.x < b.pMax.x && pt.y >= b.pMin.y && pt.y < b.pMax.y);
    }

    template<typename T, typename U>
    inline Bounds2<T> Expand(const Bounds2<T> &b, U delta) {
        Bounds2<T> ret;
        ret.pMin = b.pMin - Vector2<T>(delta, delta);
        ret.pMax = b.pMax + Vector2<T>(delta, delta);
        return ret;
    }

#pragma endregion Bounds2 Inline Functions

#pragma region Bounds3 Inline Functions

// Bounds3 Inline Functions
    template<typename T>
    inline Bounds3<T> Union(const Bounds3<T> &b, const Point3<T> &p) {
        Bounds3<T> ret;
        ret.pMin = Min(b.pMin, p);
        ret.pMax = Max(b.pMax, p);
        return ret;
    }

    template<typename T>
    inline Bounds3<T> Union(const Bounds3<T> &b1, const Bounds3<T> &b2) {
        Bounds3<T> ret;
        ret.pMin = Min(b1.pMin, b2.pMin);
        ret.pMax = Max(b1.pMax, b2.pMax);
        return ret;
    }

    template<typename T>
    inline Bounds3<T> Intersect(const Bounds3<T> &b1, const Bounds3<T> &b2) {
        Bounds3<T> b;
        b.pMin = Max(b1.pMin, b2.pMin);
        b.pMax = Min(b1.pMax, b2.pMax);
        return b;
    }

    template<typename T>
    inline bool Overlaps(const Bounds3<T> &b1, const Bounds3<T> &b2) {
        bool x = (b1.pMax.x >= b2.pMin.x) && (b1.pMin.x <= b2.pMax.x);
        bool y = (b1.pMax.y >= b2.pMin.y) && (b1.pMin.y <= b2.pMax.y);
        bool z = (b1.pMax.z >= b2.pMin.z) && (b1.pMin.z <= b2.pMax.z);
        return (x && y && z);
    }

    template<typename T>
    inline bool Inside(const Point3<T> &p, const Bounds3<T> &b) {
        return (p.x >= b.pMin.x && p.x <= b.pMax.x && p.y >= b.pMin.y && p.y <= b.pMax.y &&
                p.z >= b.pMin.z && p.z <= b.pMax.z);
    }

    template<typename T>
    inline bool InsideExclusive(const Point3<T> &p, const Bounds3<T> &b) {
        return (p.x >= b.pMin.x && p.x < b.pMax.x && p.y >= b.pMin.y && p.y < b.pMax.y &&
                p.z >= b.pMin.z && p.z < b.pMax.z);
    }

    template<typename T, typename U>
    inline auto DistanceSquared(const Point3<T> &p, const Bounds3<U> &b) {
        using TDist = decltype(T{} - U{});
        TDist dx = std::max<TDist>({0, b.pMin.x - p.x, p.x - b.pMax.x});
        TDist dy = std::max<TDist>({0, b.pMin.y - p.y, p.y - b.pMax.y});
        TDist dz = std::max<TDist>({0, b.pMin.z - p.z, p.z - b.pMax.z});
        return dx * dx + dy * dy + dz * dz;
    }

    template<typename T, typename U>
    inline auto Distance(const Point3<T> &p, const Bounds3<U> &b) {
        auto dist2 = DistanceSquared(p, b);
        return std::sqrt(float(dist2));
    }

    template<typename T, typename U>
    inline Bounds3<T> Expand(const Bounds3<T> &b, U delta) {
        Bounds3<T> ret;
        ret.pMin = b.pMin - Vector3<T>(delta, delta, delta);
        ret.pMax = b.pMax + Vector3<T>(delta, delta, delta);
        return ret;
    }

    template<typename T>
    inline bool Bounds3<T>::IntersectP(const Point3f &o, const Vector3f &d,
                                       float tMax, float *hitt0,
                                       float *hitt1) const {
        float t0 = 0, t1 = tMax;
        for (int i = 0; i < 3; ++i) {
            // Update interval for _i_th bounding box slab
            float invRayDir = 1 / d[i];
            float tNear = (pMin[i] - o[i]) * invRayDir;
            float tFar = (pMax[i] - o[i]) * invRayDir;
            // Update parametric interval from slab intersection $t$ values
            if (tNear > tFar)
                std::swap(tNear, tFar);
//                pstd::swap(tNear, tFar);
            // Update _tFar_ to ensure robust ray--bounds intersection
            tFar *= 1 + 2 * gamma(3);

            t0 = tNear > t0 ? tNear : t0;
            t1 = tFar < t1 ? tFar : t1;
            if (t0 > t1)
                return false;
        }
        if (hitt0)
            *hitt0 = t0;
        if (hitt1)
            *hitt1 = t1;
        return true;
    }

    template<typename T>
    inline bool Bounds3<T>::IntersectP(const Point3f &o, const Vector3f &d,
                                       float raytMax, const Vector3f &invDir,
                                       const int dirIsNeg[3]) const {
        const Bounds3f &bounds = *this;
        // Check for ray intersection against $x$ and $y$ slabs
        float tMin = (bounds[dirIsNeg[0]].x - o.x) * invDir.x;
        float tMax = (bounds[1 - dirIsNeg[0]].x - o.x) * invDir.x;
        float tyMin = (bounds[dirIsNeg[1]].y - o.y) * invDir.y;
        float tyMax = (bounds[1 - dirIsNeg[1]].y - o.y) * invDir.y;
        // Update _tMax_ and _tyMax_ to ensure robust bounds intersection
        tMax *= 1 + 2 * gamma(3);
        tyMax *= 1 + 2 * gamma(3);

        if (tMin > tyMax || tyMin > tMax)
            return false;
        if (tyMin > tMin)
            tMin = tyMin;
        if (tyMax < tMax)
            tMax = tyMax;

        // Check for ray intersection against $z$ slab
        float tzMin = (bounds[dirIsNeg[2]].z - o.z) * invDir.z;
        float tzMax = (bounds[1 - dirIsNeg[2]].z - o.z) * invDir.z;
        // Update _tzMax_ to ensure robust bounds intersection
        tzMax *= 1 + 2 * gamma(3);

        if (tMin > tzMax || tzMin > tMax)
            return false;
        if (tzMin > tMin)
            tMin = tzMin;
        if (tzMax < tMax)
            tMax = tzMax;

        return (tMin < raytMax) && (tMax > 0);
    }

#pragma endregion Bounds3 Inline Functions
}

#endif //JADEHARE_CORE_MATH_BOUNDS_H
