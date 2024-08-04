#include <algorithm>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

auto find_subarray_sum_circle(const std::vector<int> &nums) -> int {
  if (nums.size() == 1)
    return nums.back();

  auto sum = std::accumulate(nums.cbegin(), nums.cend(), 0);

  auto min = nums.front();
  auto max = std::accumulate(nums.cbegin() + 1, nums.cend(), nums.front(),
                             [&min, curr_max = nums.front(),
                              curr_min = nums.front()](int max, int n) mutable {
                               curr_max = std::max(curr_max + n, n);
                               max = std::max(max, curr_max);

                               curr_min = std::min(curr_min + n, n);
                               min = std::min(min, curr_min);

                               return max;
                             });
  if (sum == min)
    return max;

  return std::max(max, sum - min);
}

TEST(FindSubarraySumCircle, Cases) {
  EXPECT_EQ(find_subarray_sum_circle({1, -2, 3, -2}), 3);
  EXPECT_EQ(find_subarray_sum_circle({5, -3, 5}), 10);
  EXPECT_EQ(find_subarray_sum_circle({-3, -2, -3}), -2);
}
