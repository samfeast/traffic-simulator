#pragma once

#include "horizontal_profile.hpp"
#include "vertical_profile.hpp"
#include "vector3.hpp"

namespace simulator
{
    struct RoadPose
    {
        Vector3 position;
    };

    class RoadSegment
    {
    public:
        RoadSegment(const HorizontalProfile &horizontal,
                    const VerticalProfile &vertical,
                    const Vector3 &origin);

        double getLength() const;
        Vector3 getOrigin() const;

        [[nodiscard]] RoadPose evaluate(double s) const;

    private:
        HorizontalProfile horizontal_;
        VerticalProfile vertical_;

        Vector3 origin_;
    };
}