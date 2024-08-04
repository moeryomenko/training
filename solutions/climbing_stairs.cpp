#include <cmath>
#include <float.h>

#include <gtest/gtest.h>

constexpr auto root(double n) -> double {
  double x = n;
  double y = 1;
  double e = DBL_MIN;
  while (x - y > e) {
    x = (x + y) / 2;
    y = n / x;
  }
  return x;
}

constexpr auto root_5 = root(5);
constexpr auto gold_ratio = (1.f + root_5) / 2;
constexpr auto revers_gold_ratio = (1.f - root_5) / 2;

auto climb_stairs(int n) -> int {
  if (n < 0)
    return 0;
  if (n == 0)
    return 1;
  return std::round(
      (std::pow(gold_ratio, n + 1) - std::pow(revers_gold_ratio, n + 1)) /
      root_5);
}

TEST(ClimbStairs, Cases) {
  EXPECT_EQ(climb_stairs(2), 2);
  EXPECT_EQ(climb_stairs(3), 3);
  EXPECT_EQ(climb_stairs(4), 5);
  EXPECT_EQ(climb_stairs(35), 14930352);
}
