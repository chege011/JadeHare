//
// Created by 1129 on 2020/10/16.
//

#ifndef JADEHARE_CORE_MATH_NORMAL_H
#define JADEHARE_CORE_MATH_NORMAL_H

#include "tuple.h"

namespace jadehare {

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
}

#endif //JADEHARE_CORE_MATH_NORMAL_H
