#pragma once

namespace simulator
{
struct Vector2
{
    double x;
    double y;

    Vector2(double x_, double y_) : x(x_), y(y_) {}

    Vector2& operator+=(const Vector2& other)
    {
        x += other.x;
        y += other.y;
        return *this;
    }

    Vector2& operator-=(const Vector2& other)
    {
        x -= other.x;
        y -= other.y;
        return *this;
    }

    Vector2 operator+(const Vector2& other) const
    {
        Vector2 result = *this;
        result += other;
        return result;
    }

    Vector2 operator-(const Vector2& other) const
    {
        Vector2 result = *this;
        result -= other;
        return result;
    }
};
}  // namespace simulator