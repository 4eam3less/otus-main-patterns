#include "quadratic-equation.hpp"
#include <gtest/gtest.h>

TEST(Solve, IncorrectCoefficientA){
    EXPECT_ANY_THROW(solve(0, 1.1, 8.33));
}
TEST(Solve, NaN){
    EXPECT_ANY_THROW(solve(std::numeric_limits<double>::quiet_NaN(), -148.46, 0.3));
    EXPECT_ANY_THROW(solve(1.0, std::numeric_limits<double>::signaling_NaN(), 8.8));
    EXPECT_ANY_THROW(solve(1.0, -18.4, std::numeric_limits<double>::quiet_NaN()));
}
TEST(Solve, Infinity){
    EXPECT_ANY_THROW(solve(std::numeric_limits<double>::infinity(), 12, 1));
    EXPECT_ANY_THROW(solve(5, -std::numeric_limits<double>::infinity(), 0));
    EXPECT_ANY_THROW(solve(10, 6, std::numeric_limits<double>::infinity()));
}
TEST(Solve, calculate){
    auto result = solve(1, 0, 1);
    EXPECT_DOUBLE_EQ(result[0], 0);
    EXPECT_DOUBLE_EQ(result[1], 0);

    result = solve(1, 0, -1);
    EXPECT_DOUBLE_EQ(result[0], 1);
    EXPECT_DOUBLE_EQ(result[1], -1);

    result = solve(1, 2, 1.000000000000001);
    EXPECT_DOUBLE_EQ(result[0], -1);
    EXPECT_DOUBLE_EQ(result[1], -1);
}