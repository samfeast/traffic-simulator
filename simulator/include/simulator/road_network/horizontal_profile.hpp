#pragma once

#include <variant>

#include "simulator/road_network/vector2.hpp"

namespace simulator
{
struct HorizontalProfilePose
{
    Vector2 xy;
    Vector2 tangent;  // radians
};

class HorizontalProfile
{
   public:
    static HorizontalProfile Straight(double length);
    static HorizontalProfile Arc(double length, double param1, double param2);

    double length() const;

    HorizontalProfilePose evaluate(double s) const;

    // Add getProfileShape() to get all underlying shape parameters?
    // OR just compute pose at fixed steps with evaluate() to form polyline

   private:
    struct StraightData
    {
        HorizontalProfilePose evaluate(double s) const;
    };

    struct ArcData
    {
        double param1;
        double param2;

        HorizontalProfilePose evaluate(double s) const;
    };

    HorizontalProfile(double length, std::variant<StraightData, ArcData> data) : length_(length), data_(std::move(data))
    {
    }

    double length_;
    std::variant<StraightData, ArcData> data_;
};
}  // namespace simulator