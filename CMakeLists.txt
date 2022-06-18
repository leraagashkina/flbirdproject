cmake_minimum_required(VERSION 3.21)
project(cplusProject)

set(CMAKE_CXX_STANDARD 17)

add_executable(cplusProject main.cpp tests.cpp cmake-build-debug/flappybird.cpp flappybird.h)

enable_testing()
add_subdirectory(external/doctest)

add_executable(tests flappybird.cpp tests.cpp)
target_link_libraries(tests PUBLIC doctest)