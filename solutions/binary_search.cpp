#include <algorithm>
#include <vector>

#include <gtest/gtest.h>

auto search(const std::vector<int> &nums, int target) -> int {
  auto it = std::lower_bound(nums.cbegin(), nums.cend(), target);

  return it != nums.cend() && *it == target ? std::distance(nums.cbegin(), it)
                                            : -1;
}

TEST(BinarySearch, Cases) {
  EXPECT_EQ(search({-1, 0, 3, 5, 9, 12}, 9), 4);
  EXPECT_EQ(search({-1, 0, 3, 5, 9, 12}, 2), -1);
}
