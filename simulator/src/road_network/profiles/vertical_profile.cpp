#include "simulator/road_network/vertical_profile.hpp"

#include <stdexcept>
#include <cmath>
#include <variant>

namespace simulator
{
    // Linear constructor
    VerticalProfile VerticalProfile::Linear(double horizontal_length,
                                            double grade)
    {
        if (horizontal_length <= 0.0)
        {
            throw std::invalid_argument("horizontal_length must be positive");
        }

        double length = computeLinearLength(horizontal_length, grade);

        return VerticalProfile(
            horizontal_length,
            length,
            LinearData{
                .grade = grade,
                .direction = {
                    horizontal_length / length,
                    horizontal_length * grade / length}});
    }

    // Parabolic constructor
    VerticalProfile VerticalProfile::Parabolic(double horizontal_length,
                                               double param1,
                                               double param2)
    {
        if (horizontal_length <= 0.0)
        {
            throw std::invalid_argument("horizontal_length must be positive");
        }

        double length = computeParabolicLength(horizontal_length, param1, param2);

        return VerticalProfile(
            horizontal_length,
            length,
            ParabolicData{
                .param1 = param1,
                .param2 = param2});
    }

    double VerticalProfile::horizontalLength() const
    {
        return horizontal_length_;
    }

    double VerticalProfile::length() const
    {
        return length_;
    }

    VerticalProfilePose VerticalProfile::evaluate(double s) const
    {
        return std::visit(
            [s](const auto &profile)
            {
                return profile.evaluate(s);
            },
            data_);
    }

    // Private helpers

    double VerticalProfile::computeLinearLength(double horizontal_length, double grade)
    {
        return horizontal_length * std::sqrt(grade * grade + 1);
    }

    double VerticalProfile::computeParabolicLength(double horizontal_length, double param1, double param2)
    {
        throw std::logic_error("not implemented yet");
    }

    VerticalProfilePose VerticalProfile::LinearData::evaluate(double s) const
    {
        return VerticalProfilePose{
            .z = s * this->direction.y,
            .horizontal_distance = s * this->direction.x,
            .gradient = this->grade};
    }

    VerticalProfilePose VerticalProfile::ParabolicData::evaluate(double s) const
    {
        throw std::logic_error("not implemented yet");
    }
}
