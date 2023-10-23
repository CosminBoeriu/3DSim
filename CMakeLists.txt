cmake_minimum_required(VERSION 3.24)
project(3dSim1)

include(FetchContent)
set(BUILD_SHARED_LIBS OFF)
FETCHCONTENT_DECLARE(SFML GIT_REPOSITORY https://github.com/SFML/SFML.git GIT_TAG 2.5.1)
FETCHCONTENT_MAKEAVAILABLE(SFML)

set(CMAKE_CXX_STANDARD 23)

add_executable(3dSim1 main.cpp vector.h shape.h frustum.h matrix.h matrix.h
        linesegment.h
        screen.h
        projection.h
)

target_link_libraries(3dSim1 sfml-graphics)