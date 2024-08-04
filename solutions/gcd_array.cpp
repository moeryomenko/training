#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

auto find_gcd(const std::vector<int> &nums) -> int {
  const auto [min, max] = std::minmax_element(nums.cbegin(), nums.cend());
  return std::gcd(*min, *max);
}

TEST(FindGCD, Cases) {
  EXPECT_EQ(find_gcd({2, 5, 6, 9, 10}), 2);
  EXPECT_EQ(find_gcd({7, 5, 6, 8, 3}), 1);
  EXPECT_EQ(find_gcd({3, 3}), 3);
}
