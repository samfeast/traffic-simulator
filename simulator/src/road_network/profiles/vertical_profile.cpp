#include "simulator/road_network/vertical_profile.hpp"

#include <stdexcept>
#include <cmath>

namespace simulator
{
    VerticalProfile::VerticalProfile(VerticalProfileType type,
                                     double length,
                                     double linear_angle)
        : type_(type),
          length_(length),
          linear_angle_(linear_angle)
    {
        if (length <= 0)
        {
            throw std::invalid_argument("length must be positive");
        }
    }

    double VerticalProfile::getLength() const
    {
        return length_;
    }

    VerticalProfilePose VerticalProfile::evaluate(double s) const
    {
        switch (type_)
        {
        case VerticalProfileType::Flat:
            return evaluateFlat();
        case VerticalProfileType::Linear:
            return evaluateLinear(s);
        }

        throw std::logic_error("Failed to match profile type");
    }

    VerticalProfilePose VerticalProfile::evaluateFlat() const
    {
        return VerticalProfilePose{0.0, 0.0};
    }

    VerticalProfilePose VerticalProfile::evaluateLinear(double s) const
    {
        return VerticalProfilePose{s * sin(linear_angle_), linear_angle_};
    }
}
