#pragma once

namespace simulator
{
    struct HorizontalProfilePose
    {
        double x;
        double y;
        double theta; // radians
    };

    enum class HorizontalProfileType : int
    {
        Straight = 0,
        Arc = 1
    };

    class HorizontalProfile
    {
    public:
        HorizontalProfile(HorizontalProfileType type,
                          double length);

        HorizontalProfilePose evaluate(double s) const;

        double getLength() const;

    private:
        HorizontalProfileType type_;
        double length_;

        HorizontalProfilePose evaluateStraight(double s) const;
        HorizontalProfilePose evaluateArc(double s) const;
    };
}