#pragma once

namespace simulator
{
    struct Vector3
    {
        double x;
        double y;
        double z;

        Vector3(double x_, double y_, double z_)
            : x(x_), y(y_), z(z_) {}

        Vector3 &operator+=(const Vector3 &other)
        {
            x += other.x;
            y += other.y;
            z += other.z;
            return *this;
        }

        Vector3 &operator-=(const Vector3 &other)
        {
            x -= other.x;
            y -= other.y;
            z -= other.z;
            return *this;
        }

        Vector3 operator+(const Vector3 &other) const
        {
            Vector3 result = *this;
            result += other;
            return result;
        }

        Vector3 operator-(const Vector3 &other) const
        {
            Vector3 result = *this;
            result -= other;
            return result;
        }
    };
}