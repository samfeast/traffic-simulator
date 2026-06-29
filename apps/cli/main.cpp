#include "simulator/road_network/road_segment.hpp"
#include "simulator/road_network/horizontal_profile.hpp"
#include "simulator/road_network/vertical_profile.hpp"
#include "simulator/road_network/vector3.hpp"

#include <iostream>

int main()
{
    simulator::HorizontalProfile h{
        simulator::HorizontalProfileType::Straight,
        100.0};

    simulator::VerticalProfile v{
        simulator::VerticalProfileType::Flat,
        100.0};

    simulator::Vector3 origin{
        50.0,
        10.0,
        0.0};

    simulator::RoadSegment segment(h, v, origin);

    auto s = 10.0;

    auto pose = segment.evaluate(s);

    std::cout
        << "s=" << s
        << " x=" << pose.position.x
        << " y=" << pose.position.y
        << " z=" << pose.position.z
        << "\n";

    return 0;
}