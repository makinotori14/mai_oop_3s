#include <gtest/gtest.h>
#include "decimal.hpp"

TEST(DecimalConstructorTest, DefaultConstructor) {
    Decimal d;
    EXPECT_EQ(d.toString(), "0");
    EXPECT_EQ(d.size(), 1);
}

TEST(DecimalConstructorTest, SizeAndValue) {
    Decimal d(3, 5);
    EXPECT_EQ(d.toString(), "555");
}

TEST(DecimalConstructorTest, InitializerList) {
    Decimal d({1, 2, 3});
    EXPECT_EQ(d.toString(), "321");
}

TEST(DecimalConstructorTest, StringConstructor) {
    Decimal d("456");
    EXPECT_EQ(d.toString(), "456");
}

TEST(DecimalConstructorTest, EmptyString) {
    Decimal d("");
    EXPECT_EQ(d.toString(), "0");
}

TEST(DecimalArithmeticTest, AddBasic) {
    Decimal a("123");
    Decimal b("877");
    Decimal sum = a.add(b);
    EXPECT_EQ(sum.toString(), "1000");
}

TEST(DecimalArithmeticTest, AddWithCarry) {
    Decimal a("999");
    Decimal b("1");
    EXPECT_EQ(a.add(b).toString(), "1000");
}

TEST(DecimalArithmeticTest, SubtractBasic) {
    Decimal a("100");
    Decimal b("1");
    EXPECT_EQ(a.subtract(b).toString(), "99");
}

TEST(DecimalArithmeticTest, SubtractThrowsOnNegative) {
    Decimal a("10");
    Decimal b("20");
    EXPECT_THROW(a.subtract(b), std::invalid_argument);
}

TEST(DecimalComparisonTest, LessThan) {
    Decimal a("123");
    Decimal b("456");
    EXPECT_TRUE(a < b);
    EXPECT_FALSE(b < a);
}

TEST(DecimalComparisonTest, Equal) {
    Decimal a("789");
    Decimal b("789");
    EXPECT_TRUE(a == b);
    EXPECT_FALSE(a != b);
}

TEST(DecimalComparisonTest, CompareByLength) {
    Decimal a("999");
    Decimal b("1000");
    EXPECT_TRUE(a < b);
}

TEST(DecimalEdgeCaseTest, ZeroSubtractZero) {
    Decimal a("0"), b("0");
    EXPECT_EQ(a.subtract(b).toString(), "0");
}

TEST(DecimalEdgeCaseTest, AddZero) {
    Decimal a("123");
    Decimal b("0");
    EXPECT_EQ(a.add(b).toString(), "123");
}

TEST(DecimalEdgeCaseTest, LargeNumber) {
    Decimal a("12345678901234567890");
    Decimal b("98765432109876543210");
    Decimal sum = a.add(b);
    EXPECT_EQ(sum.toString(), "111111111011111111100");
}