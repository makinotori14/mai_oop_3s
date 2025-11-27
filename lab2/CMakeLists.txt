cmake_minimum_required(VERSION 3.14)
project(mai_207)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(include)

add_library(decimal_lib
    src/vector.cpp
    src/decimal.cpp
)

target_include_directories(decimal_lib PUBLIC include)

add_executable(decimal_app main.cpp)
target_link_libraries(decimal_app decimal_lib)

include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG v1.15.0
    TLS_VERIFY false
)
FetchContent_MakeAvailable(googletest)

add_executable(decimal_tests tests/test_decimal.cpp)
target_link_libraries(decimal_tests decimal_lib GTest::gtest_main)