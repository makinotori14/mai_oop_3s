#include <gtest/gtest.h>
#include "Hexagon.h"
#include "Octagon.h"
#include "Triangle.h"

TEST(TriangleTest, AreaCalculation) {
    Triangle tri({{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}});
    EXPECT_NEAR(static_cast<double>(tri), 0.5, 1e-9);
}

TEST(TriangleTest, CenterCalculation) {
    Triangle tri({{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}});
    auto center = tri.getCenter();
    EXPECT_NEAR(center.first, 1.0/3.0, 1e-9);
    EXPECT_NEAR(center.second, 1.0/3.0, 1e-9);
}

TEST(TriangleTest, EqualityOperator) {
    Triangle tri1({{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}});
    Triangle tri2({{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}});
    Triangle tri3({{0.0, 0.0}, {2.0, 0.0}, {0.0, 2.0}});

    EXPECT_TRUE(tri1 == tri2);
    EXPECT_FALSE(tri1 == tri3);
}

TEST(HexagonTest, AreaCalculation) {
    Hexagon hex;
    double expectedArea = 3 * std::sqrt(3) / 2.0;
    EXPECT_NEAR(static_cast<double>(hex), expectedArea, 1e-9);
}

TEST(HexagonTest, CenterCalculation) {
    Hexagon hex;
    auto center = hex.getCenter();
    EXPECT_NEAR(center.first, 0.0, 1e-9);
    EXPECT_NEAR(center.second, 0.0, 1e-9);
}

TEST(OctagonTest, AreaCalculation) {
    Octagon oct;
    double expectedArea = 2 * std::sqrt(2);
    EXPECT_NEAR(static_cast<double>(oct), expectedArea, 1e-9);
}

TEST(OctagonTest, CenterCalculation) {
    Octagon oct;
    auto center = oct.getCenter();
    EXPECT_NEAR(center.first, 0.0, 1e-9);
    EXPECT_NEAR(center.second, 0.0, 1e-9);
}

TEST(AssignmentTest, CopyAssignment) {
    Triangle tri1({{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}});
    Triangle tri2;
    tri2 = tri1;
    EXPECT_TRUE(tri1 == tri2);
}

TEST(AssignmentTest, MoveAssignment) {
    Triangle tri1({{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}});
    Triangle tri2;
    tri2 = std::move(tri1);
    Triangle expected({{0.0, 0.0}, {1.0, 0.0}, {0.0, 1.0}});
    EXPECT_TRUE(tri2 == expected);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}