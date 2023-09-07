#pragma once
#include <iostream>
#include <type_traits>

namespace MMath
{
    // General templates

    template<typename U>
    struct IsNumericType : std::is_arithmetic<U> {};

    template<typename U>
    using EnableNumeric = std::enable_if_t<IsNumericType<U>::value>;

    // Functions

    template <typename T,typename U, typename = EnableNumeric<T>, typename = EnableNumeric<U>>
    T Min(T lhs, U rhs)
    {
        return lhs < rhs ? lhs : static_cast<T>(rhs);
    }

    template <typename T, typename = EnableNumeric<T>>
    T Max(T lhs, T rhs)
    {
        return lhs > rhs ? lhs : rhs;
    }

    template <typename T, typename = EnableNumeric<T>>
    T Clamp(T value, T min, T max)
    {
        return Max<T>(min, Min<T>(value, max));
    }

    // Classes

    template <typename T, typename = EnableNumeric<T>>
    class Vec2
    {
    public:
        using Type = T;
        using Real = std::conditional_t<std::is_same_v<Type, double>, double, float>;

        template <typename U>
        using NumericCompatibleType =
        typename std::enable_if<IsNumericType<U>::value, typename std::common_type<Type, U>::type>::type;

        template <typename U>
        using Vec2Result = Vec2<NumericCompatibleType<U>>;
        
        Vec2(Type x = 0, Type y = 0) : x(x), y(y) {}

        template<typename U, typename = EnableNumeric<U>>
        Vec2(const Vec2<U>& other) : x(static_cast<Type>(other.x)), y(static_cast<Type>(other.y)) { }

        template<typename U>
        Vec2Result<U>& operator=(const Vec2<U>& other)
        {
            x = static_cast<U>(other.x);
            y = static_cast<U>(other.y);

            return *this;
        }

        template<typename U>
        Vec2Result<U> operator+(const Vec2<U>& other) const
        {
            return
            {
                static_cast<NumericCompatibleType<U>>(x + other.x),
                static_cast<NumericCompatibleType<U>>(y + other.y)
            };
        }

        template<typename U>
        Vec2Result<U> operator-(const Vec2<U>& other) const
        {
            return
            {
                static_cast<NumericCompatibleType<U>>(x - other.x),
                static_cast<NumericCompatibleType<U>>(y - other.y)
            };
        }

        template<typename U, typename = EnableNumeric<U>>
        Vec2Result<U>& operator+=(const Vec2<U> &other)
        {
            x = static_cast<Type>(x + other.x);
            y += static_cast<Type>(y + other.y);

            return *this;
        }

        template<typename U, typename = EnableNumeric<U>>
        Vec2Result<U>& operator-=(const Vec2<U> &other)
        {
            x = static_cast<Type>(x - other.x);
            y = static_cast<Type>(y - other.y);

            return *this;
        }

        // Scalar multiplication
        template <typename U>
        Vec2Result<U> operator*(U scalar) const
        {
            return { static_cast<NumericCompatibleType<U>>(x * scalar), static_cast<NumericCompatibleType<U>>(y * scalar) };
        }

        // Scalar division
        template <typename U>
        Vec2Result<U> operator/(U scalar) const
        {
            if(scalar != 0)
                return {static_cast<Type>(x / scalar), static_cast<Type>(y / scalar)};

            return { 0, 0 };
        }

        template<typename U, typename = EnableNumeric<U>>
        Type Dot(const Vec2<U> &other) const
        {
            return static_cast<Type>(x * other.x) + static_cast<Type>(y * other.y);
        }

        template<typename U, typename = EnableNumeric<U>>
        Type Cross(const Vec2<U> &other) const
        {
            return static_cast<Type>(x * other.y) - static_cast<Type>(y * other.x);
        }

        Real Length() const
        {
            return std::sqrt(x * x + y * y);
        }

        Vec2<Real> Normalize() const
        {
            Real length = Length();

            if (length != 0)
                return { static_cast<Real>(x) / length, static_cast<Real>(y) / length  };

            return {0.0f, 0.0f};
        }

        // Angle between two vectors in radians
        template<typename U, typename = EnableNumeric<U>> const
        Real Angle(const Vec2<U> &other)
        {
            return std::atan2(Cross(other), Dot(other));
        }

        template<typename U, typename = EnableNumeric<U>> const
        Real Distance(const Vec2<U> &other)
        {
            Real xGap = std::pow(static_cast<Real>(other.x - x), 2);
            Real yGap = std::pow(static_cast<Real>(other.y - y), 2);

            return std::sqrt(xGap + yGap);
        }

        template<typename U>
        Vec2Result<U> Perpendicular(bool clockwise = true) const
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