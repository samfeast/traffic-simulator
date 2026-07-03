#include "simulator/road_network/road_segment.hpp"
#include "simulator/road_network/horizontal_profile.hpp"
#include "simulator/road_network/vertical_profile.hpp"
#include "simulator/road_network/vector3.hpp"

#include <iostream>

int main()
{
    auto horizontal_length = 100.0;
    auto h = simulator::HorizontalProfile::Straight(horizontal_length);
    auto v = simulator::VerticalProfile::Linear(horizontal_length, -0.1);

    simulator::Vector3 origin{
        0.0,
        0.0,
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