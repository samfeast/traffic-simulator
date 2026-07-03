#include "simulator/road_network/vertical_profile.hpp"

#include <cmath>
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

double VerticalProfile::horizontalLength() const { return horizontal_length_; }

double VerticalProfile::length() const { return length_; }

VerticalProfilePose VerticalProfile::evaluate(double s) const
{
    return std::visit(
        [this, s](const auto& profile) { return profile.evaluate(horizontal_length_, elevation_, length_, s); }, data_);
}

// Private helpers

double VerticalProfile::computeLinearLength(double horizontal_length, double elevation)
{
    return std::sqrt(horizontal_length * horizontal_length + elevation * elevation);
}

double VerticalProfile::computeParabolicLength(double horizontal_length, double elevation, double a, double b)
{
    throw std::logic_error("not implemented yet");
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
    throw std::logic_error("not implemented yet");
}
}  // namespace simulator
