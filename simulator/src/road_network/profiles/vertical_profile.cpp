#include "simulator/road_network/vertical_profile.hpp"

#include <cmath>
#include <iostream>
#include <stdexcept>
#include <variant>

namespace simulator
{
// Linear constructor
VerticalProfile VerticalProfile::Linear(double horizontal_length, double elevation)
{
    if (horizontal_length <= 0.0)
    {
        throw std::invalid_argument("horizontal_length must be positive");
    }

    double length = computeLinearLength(horizontal_length, elevation);

    return VerticalProfile(horizontal_length, elevation, length, LinearData{});
}

// Parabolic constructor
VerticalProfile VerticalProfile::Parabolic(double horizontal_length, double elevation, double initial_gradient)
{
    if (horizontal_length <= 0.0)
    {
        throw std::invalid_argument("horizontal_length must be positive");
    }

    auto a = (elevation - initial_gradient * horizontal_length) / (horizontal_length * horizontal_length);
    auto b = initial_gradient;

    double length = computeParabolicLength(horizontal_length, elevation, a, b);

    return VerticalProfile(horizontal_length, elevation, length, ParabolicData{.a = a, .b = b});
}

// Getters
double VerticalProfile::horizontalLength() const { return horizontal_length_; }
double VerticalProfile::elevation() const { return elevation_; }
double VerticalProfile::length() const { return length_; }

// Public evaluation dispatcher
VerticalProfilePose VerticalProfile::evaluate(double s) const
{
    return std::visit(
        [this, s](const auto& profile) { return profile.evaluate(horizontal_length_, elevation_, length_, s); }, data_);
}

// Private helpers

double VerticalProfile::computeLinearLength(double x, double y) { return std::sqrt(x * x + y * y); }

double VerticalProfile::computeParabolicLength(double x, double y, double a, double b)
{
    if (std::abs(2.0 * a * x) < 1e-6)
    {
        // Fallback to linear for very shallow parabolas
        return computeLinearLength(x, y);
    }

    // NOTE: RISK HERE!
    const double u_end = 2.0 * a * x + b;
    const double u_start = b;

    const double sqrt_u_end = std::sqrt(1.0 + u_end * u_end);
    const double sqrt_u_start = std::sqrt(1.0 + u_start * u_start);

    const auto F = [](double u, double s) { return u * s + std::log(u + s); };

    return 0.25 / a * (F(u_end, sqrt_u_end) - F(u_start, sqrt_u_start));
}

VerticalProfilePose VerticalProfile::LinearData::evaluate(double horizontal_length, double elevation, double length,
                                                          double s) const
{
    auto t = s / length;
    return VerticalProfilePose{
        .z = t * elevation, .horizontal_distance = t * horizontal_length, .gradient = elevation / horizontal_length};
}

VerticalProfilePose VerticalProfile::ParabolicData::evaluate(double horizontal_length, double elevation, double length,
                                                             double s) const
{
    auto tolerance = 1e-8;

    auto s_n = s;
    // Fallback to linear for very small 2 * a * s
    auto fallback_elevation = elevation * s / length;

    double arc_length;
    double residual;
    double step;
    double slope;
    double denom;

    for (int i = 0; i < 10; i++)
    {
        arc_length = computeParabolicLength(s_n, fallback_elevation, a, b);

        residual = arc_length - s;

        if (std::abs(residual) < tolerance)
        {
            break;
        }

        slope = 2.0 * a * s_n + b;
        denom = std::sqrt(1.0 + slope * slope);

        // Avoid division issues
        if (denom < 1e-12)
        {
            break;
        }

        step = residual / denom;
        s_n -= step;

        // Also converge if step is less than tolerance
        if (std::abs(step) < tolerance)
        {
            break;
        }
    }

    auto z = a * s_n * s_n + b * s_n;
    auto gradient = 2 * a * s_n + b;

    return VerticalProfilePose{.z = z, .horizontal_distance = s_n, .gradient = gradient};
}
}  // namespace simulator
