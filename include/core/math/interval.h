//
// Created by 1129 on 2020/10/27.
//

#ifndef JADEHARE_CORE_MATH_INTERVAL_H
#define JADEHARE_CORE_MATH_INTERVAL_H

#include "jadehare.h"
#include "util/check.h"

namespace jadehare {
// Interval Definition
    template<typename Float>
    class Interval {
    public:
        // Interval Public Methods
        Interval() = default;

        constexpr Interval(Float low, Float high)
                : low(std::min(low, high)), high(std::max(low, high)) {}


        Interval
        &

        operator=(Float v) {
            low = high = v;
            return *this;
        }


        static Interval
        FromValueAndError(Float
                          v,
                          Float err
        ) {
            Interval i;
            if (err == 0)
                i.low = i.high = v;
            else {
                // Compute conservative bounds by rounding the endpoints away
                // from the middle. Note that this will be over-conservative in
                // cases where v-err or v+err are exactly representable in
                // floating-point, but it's probably not worth the trouble of
                // checking this case.
                i.low = NextFloatDown(v - err);
                i.high = NextFloatUp(v + err);
            }
            return i;
        }


        Float

        UpperBound() const { return high; }


        Float

        LowerBound() const { return low; }


        Float

        Midpoint() const { return (low + high) / 2; }


        Float

        Width() const { return high - low; }


        Float

        operator[](int i) const {
            DCHECK(i == 0 || i == 1);
            return (i == 0) ? low : high;
        }


        explicit Interval(Float v) : low(v), high(v) {}


        explicit operator Float() const { return Midpoint(); }


        bool Exactly(Float v) const { return low == v && high == v; }

        template<typename T>
        explicit Interval(const Interval<T> &i) {
            *this = i;
        }

        template<typename T>
        Interval
        &

        operator=(const Interval<T> &i) {
            low = i.LowerBound();
            high = i.UpperBound();
            if (sizeof(T) > sizeof(Float)) {
                // Assume that if Float is bigger than T, then it's more
                // precise, which seems not unreasonable...
                low = NextFloatDown(low);
                high = NextFloatUp(high);
            }
            return *this;
        }


        bool operator==(Float v) const { return Exactly(v); }


        Interval

        operator-() const { return {-high, -low}; }

        template<typename F>
        auto operator+(Interval<F> i) const
        -> Interval<decltype(Float() + F())> {
            using FR = decltype(Float() + F());
            if (Exactly(0))
                return Interval<FR>(i);
            else if (i.Exactly(0))
                return Interval<FR>(*this);

            return Interval<FR>(NextFloatDown(LowerBound() + i.LowerBound()),
                                NextFloatUp(UpperBound() + i.UpperBound()));
        }

        template<typename F>
        auto operator-(Interval<F> i) const
        -> Interval<decltype(Float() - F())> {
            using FR = decltype(Float() - F());
            if (Exactly(0))
                return Interval<FR>(-i);
            else if (i.Exactly(0))
                return Interval<FR>(*this);

            return Interval<FR>(NextFloatDown(LowerBound() - i.UpperBound()),
                                NextFloatUp(UpperBound() - i.LowerBound()));
        }

        template<typename F>
        auto operator*(Interval<F> i) const
        -> Interval<decltype(Float() * F())> {
            using FR = decltype(Float() * F());
            if (Exactly(0) || i.Exactly(0))
                return Interval<FR>(0);
            if (Exactly(1))
                return Interval<FR>(i);
            if (i.Exactly(1))
                return Interval<FR>(*this);

            FR prod[4] = {LowerBound() * i.LowerBound(), UpperBound() * i.LowerBound(),
                          LowerBound() * i.UpperBound(), UpperBound() * i.UpperBound()};
            return Interval<FR>(NextFloatDown(std::min({prod[0], prod[1], prod[2], prod[3]})),
                                NextFloatUp(std::max({prod[0], prod[1], prod[2], prod[3]})));
        }

        template<typename F>
        auto operator/(Interval<F> i) const
        -> Interval<decltype(Float() / F())> {
            using FR = decltype(Float() / F());
            if (Exactly(0))
                // Not going to worry about NaN...
                return Interval<FR>(0);
            if (i.Exactly(1))
                return Interval<FR>(*this);

            if (InRange(0, i))
                // The interval we're dividing by straddles zero, so just
                // return an interval of everything.
                return Interval<FR>(-Infinity, Infinity);

            FR div[4] = {LowerBound() / i.LowerBound(), UpperBound() / i.LowerBound(),
                         LowerBound() / i.UpperBound(), UpperBound() / i.UpperBound()};
            return Interval<FR>(NextFloatDown(std::min({div[0], div[1], div[2], div[3]})),
                                NextFloatUp(std::max({div[0], div[1], div[2], div[3]})));
        }

        template<typename F>
        bool operator==(Interval<F> i) const {
            return low == i.low && high == i.high;
        }


        bool operator!=(Float f) const { return f < low || f > high; }

        std::string ToString() const;

        template<typename F>
        Interval
        &

        operator+=(Interval<F> i) {
            *this = Interval(*this + i);
            return *this;
        }

        template<typename F>
        Interval
        &

        operator-=(Interval<F> i) {
            *this = Interval(*this - i);
            return *this;
        }

        template<typename F>
        Interval
        &

        operator*=(Interval<F> i) {
            *this = Interval(*this * i);
            return *this;
        }

        template<typename F>
        Interval
        &

        operator/=(Interval<F> i) {
            *this = Interval(*this / i);
            return *this;
        }


        Interval
        &

        operator+=(Float f) { return *this += Interval<Float>(f); }


        Interval
        &

        operator-=(Float f) { return *this -= Interval<Float>(f); }


        Interval
        &

        operator*=(Float f) { return *this *= Interval<Float>(f); }


        Interval
        &

        operator/=(Float f) { return *this /= Interval<Float>(f); }

#ifndef PBRT_IS_GPU_CODE
        static const Interval Pi;
#endif

    private:
        friend class SOA<Interval<Float>>;

        // Interval Private Members
        Float low, high;
    };

    using FloatInterval = Interval<float>;

// Interval Inline Functions
    template<typename T, typename Float>
    inline bool InRange(T v, Interval<Float> i) {
        return v >= i.LowerBound() && v <= i.UpperBound();
    }

    template<typename FloatA, typename FloatB>
    inline bool InRange(Interval<FloatA> a, Interval<FloatB> b) {
        return a.LowerBound() <= b.UpperBound() && a.UpperBound() >= b.LowerBound();
    }

    template<typename T, typename Float>
    inline
    typename std::enable_if_t<std::is_arithmetic<T>::value, Interval<Float>>
    operator+(T
              f,
              Interval<Float> i
    ) {
        return

                Interval<Float>(f)

                +
                i;
    }

    template<typename T, typename Float>
    inline
    typename std::enable_if_t<std::is_arithmetic<T>::value, Interval<Float>>
    operator-(T
              f,
              Interval<Float> i
    ) {
        return
                Interval<Float>(f)
                -
                i;
    }

    template<typename T, typename Float>
    inline
    typename std::enable_if_t<std::is_arithmetic<T>::value, Interval<Float>>
    operator*(T
              f,
              Interval<Float> i
    ) {
        return
                Interval<Float>(f)
                *
                i;
    }

    template<typename T, typename Float>
    inline
    typename std::enable_if_t<std::is_arithmetic<T>::value, Interval<Float>>
    operator/(T
              f,
              Interval<Float> i
    ) {
        return
                Interval<Float>(f)
                /
                i;
    }

    template<typename T, typename Float>
    inline
    typename std::enable_if_t<std::is_arithmetic<T>::value, Interval<Float>>
    operator+(Interval<Float>
              i,
              T f
    ) {
        return i +
               Interval<Float>(f);
    }

    template<typename T, typename Float>
    inline
    typename std::enable_if_t<std::is_arithmetic<T>::value, Interval<Float>>
    operator-(Interval<Float>
              i,
              T f
    ) {
        return i -
               Interval<Float>(f);
    }

    template<typename T, typename Float>
    inline
    typename std::enable_if_t<std::is_arithmetic<T>::value, Interval<Float>>
    operator*(Interval<Float>
              i,
              T f
    ) {
        return
                i * Interval<Float>(f);
    }

    template<typename T, typename Float>
    inline
    typename std::enable_if_t<std::is_arithmetic<T>::value, Interval<Float>>
    operator/(Interval<Float>
              i,
              T f
    ) {
        return i /
               Interval<Float>(f);
    }

    template<typename Float>
    inline Float
    Floor(Interval<Float>
          i) {
        return
                std::floor(i
                                   .

                                           LowerBound()

                );
    }

    template<typename Float>
    inline Float
    Ceil(Interval<Float>
         i) {
        return
                std::ceil(i
                                  .

                                          UpperBound()

                );
    }

    template<typename Float>
    inline Float
    floor(Interval<Float>
          i) {
        return
                Floor(i);
    }

    template<typename Float>
    inline Float
    ceil(Interval<Float>
         i) {
        return
                Ceil(i);
    }

    template<typename Float>
    inline Float
    Min(Interval<Float>
        a,
        Interval<Float> b
    ) {
        return
                std::min(a
                                 .

                                         LowerBound(), b

                                 .

                                         LowerBound()

                );
    }

    template<typename Float>
    inline Float
    Max(Interval<Float>
        a,
        Interval<Float> b
    ) {
        return
                std::max(a
                                 .

                                         UpperBound(), b

                                 .

                                         UpperBound()

                );
    }

    template<typename Float>
    inline Float
    min(Interval<Float>
        a,
        Interval<Float> b
    ) {
        return
                Min(a, b
                );
    }

    template<typename Float>
    inline Float
    max(Interval<Float>
        a,
        Interval<Float> b
    ) {
        return
                Max(a, b
                );
    }

    template<typename Float>
    inline Interval<Float>
    Sqrt(Interval<Float>
         i) {
        return
                Interval<Float>(std::max<Float>(0, NextFloatDown(std::sqrt(i.LowerBound()))),
                                NextFloatUp(std::sqrt(i.UpperBound()))
                );
    }

    template<typename Float>
    inline Interval<Float>
    sqrt(Interval<Float>
         i) {
        return
                Sqrt(i);
    }

    template<typename Float>
    inline Interval<Float>
    Sqr(Interval<Float>
        i) {
        Float slow = Sqr(i.LowerBound()), shigh = Sqr(i.UpperBound());
        if (slow > shigh)
            pstd::swap(slow, shigh
            );
        if (InRange(0, i))
            return Interval<Float>(0,
                                   NextFloatUp(shigh)
            );
        return
                Interval<Float>(NextFloatDown(slow), NextFloatUp(shigh)
                );
    }

    template<typename FloatA, typename FloatB, typename FloatC>
    inline auto FMA(Interval<FloatA> a, Interval<FloatB> b, Interval<FloatC> c)

    -> Interval<decltype(FloatA() * FloatB() + FloatC())> {
        using FT = decltype(FloatA() * FloatB() + FloatC());
        Float low =
                NextFloatDown(std::min({FMA(a.LowerBound(), b.LowerBound(), c.LowerBound()),
                                        FMA(a.UpperBound(), b.LowerBound(), c.LowerBound()),
                                        FMA(a.LowerBound(), b.UpperBound(), c.LowerBound()),
                                        FMA(a.UpperBound(), b.UpperBound(), c.LowerBound())}));
        Float high =
                NextFloatUp(std::max({FMA(a.LowerBound(), b.LowerBound(), c.UpperBound()),
                                      FMA(a.UpperBound(), b.LowerBound(), c.UpperBound()),
                                      FMA(a.LowerBound(), b.UpperBound(), c.UpperBound()),
                                      FMA(a.UpperBound(), b.UpperBound(), c.UpperBound())}));
        return
                Interval<FT>(low, high
                );
    }

    template<typename Float>
    inline Interval<Float>
    DifferenceOfProducts(Interval<Float>
                         a,
                         Interval<Float> b,
                         Interval<Float>
                         c,
                         Interval<Float> d
    ) {
        Float ab[4] = {a.LowerBound() * b.LowerBound(), a.UpperBound() * b.LowerBound(),
                       a.LowerBound() * b.UpperBound(), a.UpperBound() * b.UpperBound()};
        Float abLow = std::min({ab[0], ab[1], ab[2], ab[3]});
        Float abHigh = std::max({ab[0], ab[1], ab[2], ab[3]});
        int abLowIndex = abLow == ab[0] ? 0 : (abLow == ab[1] ? 1 : (abLow == ab[2] ? 2 : 3));
        int abHighIndex =
                abHigh == ab[0] ? 0 : (abHigh == ab[1] ? 1 : (abHigh == ab[2] ? 2 : 3));

        Float cd[4] = {c.LowerBound() * d.LowerBound(), c.UpperBound() * d.LowerBound(),
                       c.LowerBound() * d.UpperBound(), c.UpperBound() * d.UpperBound()};
        Float cdLow = std::min({cd[0], cd[1], cd[2], cd[3]});
        Float cdHigh = std::max({cd[0], cd[1], cd[2], cd[3]});
        int cdLowIndex = cdLow == cd[0] ? 0 : (cdLow == cd[1] ? 1 : (cdLow == cd[2] ? 2 : 3));
        int cdHighIndex =
                cdHigh == cd[0] ? 0 : (cdHigh == cd[1] ? 1 : (cdHigh == cd[2] ? 2 : 3));

// Invert cd Indices since it's subtracted...
        Float low = DifferenceOfProducts(a[abLowIndex & 1], b[abLowIndex >> 1],
                                         c[cdHighIndex & 1], d[cdHighIndex >> 1]);
        Float high = DifferenceOfProducts(a[abHighIndex & 1], b[abHighIndex >> 1],
                                          c[cdLowIndex & 1], d[cdLowIndex >> 1]);
        DCHECK_LE(low, high
        );

        return {
                NextFloatDown(NextFloatDown(low)
                ),
                NextFloatUp(NextFloatUp(high)
                )};
    }

    template<typename Float>
    inline Interval<Float>
    SumOfProducts(Interval<Float>
                  a,
                  Interval<Float> b,
                  Interval<Float>
                  c,
                  Interval<Float> d
    ) {
        return
                DifferenceOfProducts(a, b,
                                     -c, d);
    }

    template<typename T, typename Float>
    inline
    typename std::enable_if_t<std::is_arithmetic<T>::value, Interval<Float>>
    MulPow2(T
            s,
            Interval<Float> i
    ) {
        return
                MulPow2(i, s
                );
    }

    template<typename T, typename Float>
    inline
    typename std::enable_if_t<std::is_arithmetic<T>::value, Interval<Float>>
    MulPow2(Interval<Float>
            i,
            T s
    ) {
        T as = std::abs(s);
        if (as < 1)
                DCHECK_EQ(1 / as, 1ull << Log2Int(1 / as));
        else
                DCHECK_EQ(as,
                          1ull <<
                               Log2Int(as)
                );

// Multiplication by powers of 2 is exaact
        return
                Interval<Float>(std::min(i.LowerBound() * s, i.UpperBound() * s),
                                std::max(i.LowerBound() * s, i.UpperBound() * s)
                );
    }

    template<typename Float>
    inline Interval<Float>
    Abs(Interval<Float>
        i) {
        if (i.

                LowerBound()

            >= 0)
// The entire interval is greater than zero, so we're all set.
            return
                    i;
        else if (i.

                UpperBound()

                 <= 0)
// The entire interval is less than zero.
            return Interval<Float>(-i.

                                           UpperBound(),

                                   -i.

                                           LowerBound()

            );
        else
// The interval straddles zero.
            return Interval<Float>(0, std::max(-i.

                    LowerBound(), i

                                                       .

                                                               UpperBound()

            ));
    }

    template<typename Float>
    inline Interval<Float>
    abs(Interval<Float>
        i) {
        return
                Abs(i);
    }

    template<typename Float>
    inline Interval<Float>
    ACos(Interval<Float>
         i) {
        Float low = std::acos(std::min<Float>(1, i.UpperBound()));
        Float high = std::acos(std::max<Float>(-1, i.LowerBound()));

        return
                Interval<Float>(std::max<Float>(0, NextFloatDown(low)), NextFloatUp(high)
                );
    }

    template<typename Float>
    inline Interval<Float>
    Sin(Interval<Float>
        i) {
        CHECK_GE(i
                         .

                                 LowerBound(),

                 -1e-16);
        CHECK_LE(i
                         .

                                 UpperBound(),

                 2.0001 * Pi);
        Float low = std::sin(std::max<Float>(0, i.LowerBound()));
        Float high = std::sin(i.UpperBound());
        if (low > high)
            pstd::swap(low, high
            );
        low = std::max<Float>(-1, NextFloatDown(low));
        high = std::min<Float>(1, NextFloatUp(high));
        if (
                InRange(Pi
                        / 2, i))
            high = 1;
        if (InRange((3.f / 2.f) * Pi, i))
            low = -1;

        return
                Interval<Float>(low, high
                );
    }

    template<typename Float>
    inline Interval<Float>
    Cos(Interval<Float>
        i) {
        CHECK_GE(i.LowerBound(),

                 -1e-16);
        CHECK_LE(i
                         .

                                 UpperBound(),

                 2.0001 * Pi);
        Float low = std::cos(std::max<Float>(0, i.LowerBound()));
        Float high = std::cos(i.UpperBound());
        if (low > high)
            pstd::swap(low, high
            );
        low = std::max<Float>(-1, NextFloatDown(low));
        high = std::min<Float>(1, NextFloatUp(high));
        if (
                InRange(Pi, i
                ))
            low = -1;

        return
                Interval<Float>(low, high
                );
    }

    template<typename Float>
    inline bool Quadratic(Interval<Float> a, Interval<Float> b,
                          Interval<Float> c, Interval<Float> *t0,
                          Interval<Float> *t1) {
        // Find quadratic discriminant
        Interval<Float> discrim = DifferenceOfProducts(b, b, MulPow2(4, a), c);
        if (discrim.LowerBound() < 0)
            return false;
        Interval<Float> floatRootDiscrim = Sqrt(discrim);

        // Compute quadratic _t_ values
        Interval<Float> q;
        if ((Float) b < 0)
            q = MulPow2(-.5, b - floatRootDiscrim);
        else
            q = MulPow2(-.5, b + floatRootDiscrim);
        *t0 = q / a;
        *t1 = c / q;
        if (t0->LowerBound() > t1->LowerBound())
            pstd::swap(*t0, *t1);
        return true;
    }

    template<typename Float>
    inline Interval<Float> SumSquares(Interval<Float> i) {
        return Sqr(i);
    }

    template<typename Float, typename... Args>
    inline Interval<Float> SumSquares(Interval<Float> i, Args... args) {
        Interval<Float> ss = FMA(i, i, SumSquares(args...));
        return Interval<Float>(std::max<Float>(0, ss.LowerBound()), ss.UpperBound());
    }
}
#endif //JADEHARE_CORE_MATH_INTERVAL_H
