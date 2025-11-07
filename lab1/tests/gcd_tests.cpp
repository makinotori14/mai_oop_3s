#include <gtest/gtest.h>
#include "gcd.h"

TEST(Gcd, Basic) {
    EXPECT_EQ(lab1::gcd(12, 18), 6);
    EXPECT_EQ(lab1::gcd(100, 10), 10);
    EXPECT_EQ(lab1::gcd(17, 13), 1);
}

TEST(Gcd, WithZero) {
    EXPECT_EQ(lab1::gcd(0, 0), 0);
    EXPECT_EQ(lab1::gcd(0, 5), 5);
    EXPECT_EQ(lab1::gcd(7, 0), 7);
}

TEST(Gcd, Negatives) {
    EXPECT_EQ(lab1::gcd(-12, 18), 6);
    EXPECT_EQ(lab1::gcd(12, -18), 6);
    EXPECT_EQ(lab1::gcd(-12, -18), 6);
}

TEST(Gcd, Symmetry) {
    EXPECT_EQ(lab1::gcd(18, 12), lab1::gcd(12, 18));
}
