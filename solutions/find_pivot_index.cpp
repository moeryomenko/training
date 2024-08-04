#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

auto find_pivot_index(const std::vector<int> &nums) -> int {
  auto is_pivot = [sum = std::accumulate(nums.cbegin(), nums.cend(), 0),
                   psum = 0](int n) mutable {
    if (sum - psum - n == psum)
      return true;
    psum += n;
    return false;
  };
  auto it = std::find_if(nums.cbegin(), nums.cend(), is_pivot);
  return it != nums.cend() ? std::distance(nums.cbegin(), it) : -1;
}

TEST(FindPivotIndex, Cases) {
  EXPECT_EQ(find_pivot_index(std::vector{1, 7, 3, 6, 5, 6}), 3);
  EXPECT_EQ(find_pivot_index(std::vector{1, 2, 3}), -1);
}
