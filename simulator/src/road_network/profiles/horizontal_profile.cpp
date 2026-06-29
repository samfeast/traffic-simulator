#include "simulator/road_network/horizontal_profile.hpp"

#include <stdexcept>

namespace simulator
{
    HorizontalProfile::HorizontalProfile(HorizontalProfileType type,
                                         double length)
        : type_(type),
          length_(length)
    {
        if (length <= 0)
        {
            throw std::invalid_argument("length must be positive");
        }
    }

    double HorizontalProfile::getLength() const
    {
        return length_;
    }

    HorizontalProfilePose HorizontalProfile::evaluate(double s) const
    {
        switch (type_)
        {
        case HorizontalProfileType::Straight:
            return evaluateStraight(s);
        case HorizontalProfileType::Arc:
            return evaluateArc(s);
        }

        throw std::logic_error("Failed to match profile type");
    }

    HorizontalProfilePose HorizontalProfile::evaluateStraight(double s) const
    {
        return HorizontalProfilePose{s, 0.0, 0.0};
    }

    HorizontalProfilePose HorizontalProfile::evaluateArc(double s) const
    {
        // TODO
        return HorizontalProfilePose{0.0, 0.0, 0.0};
    }
}
