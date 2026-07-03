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
                                      double elevation);

        static VerticalProfile Parabolic(double horizontal_length,
                                         double elevation,
                                         double initial_gradient);

        double horizontalLength() const;
        double elevation() const;
        double length() const;

        VerticalProfilePose evaluate(double s) const; // s is distance along road centreline

        // Add getProfileShape() to get all underlying shape parameters?
        // OR just compute pose at fixed steps with evaluate() to form polyline

    private:
        struct LinearData
        {
            VerticalProfilePose evaluate(double horizontal_length,
                                         double elevation,
                                         double length,
                                         double s) const;
        };

        struct ParabolicData
        {
            double a;
            double b; // b = initial gradient

            VerticalProfilePose evaluate(double horizontal_length,
                                         double elevation,
                                         double length,
                                         double s) const;
        };

        VerticalProfile(double horizontal_length,
                        double elevation,
                        double length,
                        std::variant<LinearData, ParabolicData> data)
            : horizontal_length_(horizontal_length),
              elevation_(elevation),
              length_(length),
              data_(std::move(data)) {}

        double horizontal_length_;
        double elevation_;
        double length_;
        std::variant<LinearData, ParabolicData> data_;

        static double computeLinearLength(double horizontal_length,
                                          double elevation);
        static double computeParabolicLength(double horizontal_length,
                                             double elevation,
                                             double a,
                                             double b);
    };
}