#include "simulator/road_network/horizontal_profile.hpp"

#include <stdexcept>

namespace simulator
{
    // Straight constructor
    HorizontalProfile HorizontalProfile::Straight(double length)
    {
        if (length <= 0.0)
        {
            throw std::invalid_argument("length must be positive");
        }

        return HorizontalProfile(
            length,
            StraightData{});
    }

    // Arc constructor
    HorizontalProfile HorizontalProfile::Arc(double length,
                                             double param1,
                                             double param2)
    {
        if (length <= 0.0)
        {
            throw std::invalid_argument("length must be positive");
        }

        return HorizontalProfile(
            length,
            ArcData{
                .param1 = param1,
                .param2 = param2});
    }

    double HorizontalProfile::length() const
    {
        return length_;
    }

    HorizontalProfilePose HorizontalProfile::evaluate(double s) const
    {
        return std::visit(
            [s](const auto &profile)
            {
                return profile.evaluate(s);
            },
            data_);
    }

    // Private helpers

    HorizontalProfilePose HorizontalProfile::StraightData::evaluate(double s) const
    {
        return HorizontalProfilePose{
            .xy = Vector2(s, 0.0),
            .tangent = Vector2(1.0, 0.0)};
    }

    HorizontalProfilePose HorizontalProfile::ArcData::evaluate(double s) const
    {
        throw std::logic_error("not implemented yet");
    }
}
