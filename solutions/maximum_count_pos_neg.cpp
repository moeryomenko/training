#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <vector>

#include <gtest/gtest.h>

auto maximumCount(const std::vector<int> &nums) -> int {
  auto [last_neg, first_pos] = std::equal_range(nums.cbegin(), nums.cend(), 0);
  return std::max(std::distance(nums.cbegin(), last_neg),
                  std::distance(first_pos, nums.cend()));
}

TEST(MaximumCountPositiveNegative, Cases) {
  EXPECT_EQ(maximumCount({-2, -1, -1, 1, 2, 3}), 3);
  EXPECT_EQ(maximumCount({-3, -2, -1, 0, 0, 1, 2}), 3);
  EXPECT_EQ(maximumCount({5, 20, 66, 1314}), 4);
}
