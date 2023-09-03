#pragma once
#include <iostream>
#include <type_traits>

namespace MMath
{
    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    T Min(T lhs, T rhs)
    {
        return lhs < rhs ? lhs : rhs;
    }

    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    T Max(T lhs, T rhs)
    {
        return lhs > rhs ? lhs : rhs;
    }

    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    T Clamp(T value, T min, T max)
    {
        return Max<T>(min, Min<T>(value, max));
    }

    template <typename T, typename = std::enable_if_t<std::is_arithmetic_v<T>>>
    class Vec2
    {
    public:
        using Real = std::conditional_t<std::is_same_v<T, double>, double, float>;
        using Type = T;

        Vec2(T x = 0, T y = 0) : x(x), y(y) {}
        Vec2(const Vec2& other) : x(other.x), y(other.y) { }

        Vec2& operator=(const Vec2<T> &other)
        {
            x = static_cast<Type>(other.x);
            y = static_cast<Type>(other.y);

            return *this;
        }

        Vec2 operator+(const Vec2 &other)
        {
            return {x + other.x, y + other.y};
        }

        Vec2 operator-(const Vec2 &other)
        {
            return {x - other.x, y - other.y};
        }

        Vec2& operator+=(const Vec2 &other)
        {
            x += other.x;
            y += other.y;

            return *this;
        }

        Vec2& operator-=(const Vec2 &other)
        {
            x -= other.x;
            y -= other.y;

            return *this;
        }

        // Scalar multiplication
        template <typename U>
        typename std::enable_if<std::is_arithmetic<U>::value, Vec2<T>>::type
        operator*(U scalar)
        {
            return {x * scalar, y * scalar};
        }

        // Scalar division
        template <typename U>
        typename std::enable_if<std::is_arithmetic<U>::value, Vec2<T>>::type
        operator/(U scalar)
        {
            return {x / scalar, y / scalar};
        }

        T Dot(const Vec2 &other)
        {
            return {x * other.x + y * other.y};
        }

        T Cross(const Vec2 &other)
        {
            return {x * other.y - y * other.x};
        }

        Real Length()
        {
            return std::sqrt(static_cast<float>(x * x + y * y));
        }

        Vec2<Real> Normalize()
        {
            Real length = Length();

            if (length != 0)
            {
                return Vec2<Real>{ *this / length };
            }

            return {0.0f, 0.0f};
        }

        // Angle between two vectors in radians
        auto Angle(const Vec2 &other)
        {
            if constexpr (std::is_same_v<T, double>)
                return std::atan2(Cross(other), Dot(other));
            else
                return static_cast<float>(std::atan2(Cross(other), Dot(other)));
        }

        T Distance(const Vec2 &other)
        {
            using CastType = typename std::conditional<std::is_same<T, double>::value, double, float>::type;

            CastType xGap = std::pow(static_cast<CastType>(other.x - x), 2);
            CastType yGap = std::pow(static_cast<CastType>(other.y - y), 2);

            return std::sqrt(xGap + yGap);
        }

        Vec2 Perpendicular(bool clockwise = true)
        {
            if (clockwise)
                return {y, -x};
            else
                return {-y, x};
        }

        friend std::ostream &operator<<(std::ostream &os, const Vec2<T> &vec)
        {
            return (os << "(" << vec.x << ", " << vec.y << ")");
        }

    public:
        T x;
        T y;
    };

    using dVec2 = Vec2<double>;
    using fVec2 = Vec2<float>;
    using iVec2 = Vec2<int>;
}