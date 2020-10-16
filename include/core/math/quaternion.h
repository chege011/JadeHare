//
// Created by 1129 on 2020/10/16.
//

#ifndef JADEHARE_CORE_MATH_QUATERNION_H
#define JADEHARE_CORE_MATH_QUATERNION_H

#include "jadehare.h"
#include "mathematics.h"

namespace jadehare{
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
        Quaternion operator*(float f) const { return {w * f, x * f, y * f, z * f}; }

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

#pragma region Quaternion Inline Functions
// Quaternion Inline Functions

    inline Quaternion operator*(float f, const Quaternion &q) {
        return q * f;
    }


    inline float Dot(const Quaternion &q1, const Quaternion &q2) {
        return glm::dot(static_cast<glm::quat>(q1), static_cast<glm::quat>(q2));
    }


    inline float Length(const Quaternion &q) {
        return glm::length(static_cast<glm::quat>(q));
    }

    inline Quaternion Normalize(const Quaternion &q) {
        DCHECK_GT(Length(q), 0);
        return q / Length(q);
    }


    inline float AngleBetween(const Quaternion &q1, const Quaternion &q2) {
        if (Dot(q1, q2) < 0)
            return Pi - 2 * glm::asin(Length(q1 + q2) / 2);
        else
            return 2 * glm::asin(Length(q2 - q1) / 2);
    }

// http://www.plunk.org/~hatch/rightway.php

//    inline Quaternion Slerp(float t, const Quaternion &q1, const Quaternion &q2) {
//        float theta = AngleBetween(q1, q2);
//        float sinThetaOverTheta = SinXOverX(theta);
//        return q1 * (1 - t) * SinXOverX((1 - t) * theta) / sinThetaOverTheta +
//               q2 * t * SinXOverX(t * theta) / sinThetaOverTheta;
//    }
#pragma endregion Quaternion Inline Functions
}

#endif //JADEHARE_CORE_MATH_QUATERNION_H
