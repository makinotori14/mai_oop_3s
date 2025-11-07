cmake_minimum_required(VERSION 3.16)
project(Lab01 VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_library(lab1_lib
    src/gcd.cpp
)
target_include_directories(lab1_lib
    PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include
)

add_executable(lab1_app
    src/main.cpp
)
target_link_libraries(lab1_app PRIVATE lab1_lib)

include(CTest)
if (BUILD_TESTING)
  include(FetchContent)
  set(INSTALL_GTEST OFF)
  set(BUILD_GMOCK OFF)
  set(BUILD_GTEST ON)

  FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
  )
  FetchContent_MakeAvailable(googletest)

  add_executable(lab1_tests
      tests/gcd_tests.cpp
  )
  target_link_libraries(lab1_tests PRIVATE lab1_lib GTest::gtest_main)

  include(GoogleTest)
  gtest_discover_tests(lab1_tests)
endif()

message(STATUS "Build configuration complete")
