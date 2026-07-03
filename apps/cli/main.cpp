#include <iostream>

#include "simulator/road_network/horizontal_profile.hpp"
#include "simulator/road_network/road_segment.hpp"
#include "simulator/road_network/vector3.hpp"
#include "simulator/road_network/vertical_profile.hpp"

int main()
{
    auto horizontal_length = 100.0;
    auto h = simulator::HorizontalProfile::Straight(horizontal_length);
    auto v = simulator::VerticalProfile::Parabolic(horizontal_length, -50.0, -1.0);

    simulator::Vector3 origin{0.0, 0.0, 0.0};

    simulator::RoadSegment segment(h, v, origin);

    auto s = 100.0;

    auto pose = segment.evaluate(s);

    std::cout << "s=" << s << " x=" << pose.position.x << " y=" << pose.position.y << " z=" << pose.position.z << "\n";

    return 0;
}