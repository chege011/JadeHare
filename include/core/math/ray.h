//
// Created by 1129 on 2020/10/27.
//

#ifndef JADEHARE_CORE_MATH_RAY_H
#define JADEHARE_CORE_MATH_RAY_H

#include "jadehare.h"
#include "mathematics.h"
#include "vector.h"
#include "point.h"
#include "normal.h"
#include "core/volumeScattering/medium.h"

namespace jadehare {

// Ray Definition
    class Ray {
    public:
        // Ray Public Methods
        
        bool HasNaN() const { return (o.HasNaN() || d.HasNaN()); }

        std::string ToString() const;

        Ray() = default;

        
        Ray(const Point3f &o, const Vector3f &d, float time = 0.f,
            MediumHandle medium = nullptr)
                : o(o), d(d), time(time), medium(medium) {}

        
        Point3f operator()(float t) const { return o + d * t; }

        // Ray Public Members
        Point3f o;
        Vector3f d;
        float time = 0;
        MediumHandle medium = nullptr;
    };

// RayDifferential Definition
    class RayDifferential : public Ray {
    public:
        // RayDifferential Public Methods
        RayDifferential() = default;

        
        RayDifferential(const Point3f &o, const Vector3f &d, float time = 0.f,
                        MediumHandle medium = nullptr)
                : Ray(o, d, time, medium) {}

        
        explicit RayDifferential(const Ray &ray) : Ray(ray) {}

        void ScaleDifferentials(float s) {
            rxOrigin = o + (rxOrigin - o) * s;
            ryOrigin = o + (ryOrigin - o) * s;
            rxDirection = d + (rxDirection - d) * s;
            ryDirection = d + (ryDirection - d) * s;
        }

        
//        bool HasNaN() const {
//            return Ray::HasNaN() ||
//                   (hasDifferentials && (rxOrigin.HasNaN() || ryOrigin.HasNaN() ||
//                                         rxDirection.HasNaN() || ryDirection.HasNaN()));
//        }

        std::string ToString() const;

        // RayDifferential Public Members
        bool hasDifferentials = false;
        Point3f rxOrigin, ryOrigin;
        Vector3f rxDirection, ryDirection;
    };

// Ray Inline Functions
     inline Point3f OffsetRayOrigin(Point3fi pi, Normal3f n, Vector3f w) {
        // Find vector _offset_ to corner of error bounds and compute initial _po_
        float d = Dot(Abs(n), pi.Error());
        Vector3f offset = d * Vector3f(n);
        if (Dot(w, n) < 0)
            offset = -offset;
        Point3f po = Point3f(pi) + offset;

        // Round offset point _po_ away from _p_
        for (int i = 0; i < 3; ++i) {
            if (offset[i] > 0)
                po[i] = NextFloatUp(po[i]);
            else if (offset[i] < 0)
                po[i] = NextFloatDown(po[i]);
        }

        return po;
    }

     inline Ray SpawnRay(Point3fi pi, Normal3f n, float time, Vector3f d) {
        return Ray(OffsetRayOrigin(pi, n, d), d, time);
    }

     inline Ray SpawnRayTo(Point3fi pFrom, Normal3f n, float time, Point3f pTo) {
        Vector3f d = pTo - Point3f(pFrom);
        return SpawnRay(pFrom, n, time, d);
    }

     inline Ray SpawnRayTo(Point3fi pFrom, Normal3f nFrom, float time,
                                       Point3fi pTo, Normal3f nTo) {
        Point3f pf = OffsetRayOrigin(pFrom, nFrom, Point3f(pTo) - Point3f(pFrom));
        Point3f pt = OffsetRayOrigin(pTo, nTo, pf - Point3f(pTo));
        return Ray(pf, pt - pf, time);
    }
}

#endif //JADEHARE_CORE_MATH_RAY_H
