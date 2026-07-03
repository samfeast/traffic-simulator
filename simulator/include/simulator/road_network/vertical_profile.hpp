#pragma once

#include "simulator/road_network/vector2.hpp"

#include <variant>

namespace simulator
{
    struct VerticalProfilePose
    {
        double z;
        double horizontal_distance;
        double gradient; // dz / ds == rise / run
    };

    class VerticalProfile
    {
    public:
        static VerticalProfile Linear(double horizontal_length,
                                      double grade);

        static VerticalProfile Parabolic(double horizontal_length,
                                         double param1,
                                         double param2);

        double horizontalLength() const;
        double length() const;

        VerticalProfilePose evaluate(double s) const; // s is distance along road centreline

        // Add getProfileShape() to get all underlying shape parameters?
        // OR just compute pose at fixed steps with evaluate() to form polyline

    private:
        struct LinearData
        {
            double grade;
            // computed and cached
            Vector2 direction;

            VerticalProfilePose evaluate(double s) const;
        };

        struct ParabolicData
        {
            // placeholders
            double param1;
            double param2;

            VerticalProfilePose evaluate(double s) const;
        };

        VerticalProfile(double horizontal_length,
                        double length,
                        std::variant<LinearData, ParabolicData> data)
            : horizontal_length_(horizontal_length),
              length_(length),
              data_(std::move(data)) {}

        double horizontal_length_;
        double length_;
        std::variant<LinearData, ParabolicData> data_;

        static double computeLinearLength(double horizontal_length, double grade);
        static double computeParabolicLength(double horizontal_length, double param1, double param2);
    };
}