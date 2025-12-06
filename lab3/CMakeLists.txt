cmake_minimum_required(VERSION 3.14)
project(Lab03)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

enable_testing()

include(FetchContent)

set(INSTALL_GTEST OFF)
set(BUILD_GMOCK ON)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0
)

FetchContent_MakeAvailable(googletest)

add_executable(lab03
    src/main.cpp
    src/Figure.cpp
    src/Hexagon.cpp
    src/Octagon.cpp
    src/Triangle.cpp
)

target_include_directories(lab03 PRIVATE include)

add_executable(tests
    tests/test.cpp
    src/Figure.cpp
    src/Hexagon.cpp
    src/Octagon.cpp
    src/Triangle.cpp
)

target_link_libraries(tests gtest_main)
target_include_directories(tests PRIVATE include)