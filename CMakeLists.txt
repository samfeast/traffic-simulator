cmake_minimum_required(VERSION 3.20)

project(TrafficSimulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(simulator_core
    simulator/src/road_network/road_segment.cpp
    simulator/src/road_network/profiles/horizontal_profile.cpp
    simulator/src/road_network/profiles/vertical_profile.cpp
)

target_include_directories(simulator_core PUBLIC
    simulator/include
)

add_executable(simulator_cli
    apps/cli/main.cpp
)

target_link_libraries(simulator_cli PRIVATE simulator_core)

target_compile_options(simulator_core PRIVATE
    -Wall -Wextra -Wpedantic
)