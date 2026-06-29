#pragma once

namespace simulator
{
    struct VerticalProfilePose
    {
        double z;
        double theta; // radians
    };

    enum class VerticalProfileType : int
    {
        Flat = 0,
        Linear = 1
    };

    class VerticalProfile
    {
    public:
        VerticalProfile(VerticalProfileType type,
                        double length,
                        double linear_angle = 0.0);

        VerticalProfilePose evaluate(double s) const;

        double getLength() const;

    private:
        VerticalProfileType type_;
        double length_;

        double linear_angle_; // radians, only used for linear type

        VerticalProfilePose evaluateFlat() const;
        VerticalProfilePose evaluateLinear(double s) const;
    };
}