#include "simulator/road_network/road_segment.hpp"

#include <stdexcept>

namespace simulator
{
    RoadSegment::RoadSegment(const HorizontalProfile &horizontal,
                             const VerticalProfile &vertical,
                             const Vector3 &origin)
        : horizontal_(horizontal),
          vertical_(vertical),
          origin_(origin)
    {
        if (horizontal_.getLength() != vertical_.getLength())
        {
            throw std::invalid_argument("Profile length mismatch");
        }
    }

    double RoadSegment::getLength() const
    {
        // length guaranteed to match for both horizontal and vertical
        return horizontal_.getLength();
    }

    Vector3 RoadSegment::getOrigin() const
    {
        return origin_;
    }

    RoadPose RoadSegment::evaluate(double s) const
    {
        if (s < 0 || s > getLength())
        {
            throw std::out_of_range("s out of bounds");
        }

        auto horizontalPose = horizontal_.evaluate(s);
        auto verticalPose = vertical_.evaluate(s);

        // TODO: Add orientation data to pose (as quaternion?)
        return RoadPose{
            origin_ + Vector3{horizontalPose.x,
                              horizontalPose.y,
                              verticalPose.z}};
    }
}