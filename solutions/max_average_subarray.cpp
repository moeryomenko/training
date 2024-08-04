#include <algorithm>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

auto max_avg_subarray(const std::vector<int> &nums, int k) -> double {
  auto sum = std::accumulate(nums.cbegin(), nums.cbegin() + k, 0);
  return std::accumulate(
      nums.cbegin() + k, nums.cend(), static_cast<double>(sum) / k,
      [k, &sum, prev = nums.cbegin()](double avg, int n) mutable {
        sum += n - *prev++;
        return std::max(avg, static_cast<double>(sum) / k);
      });
}

TEST(MaxAverageSubarray, Cases) {
  EXPECT_EQ(max_avg_subarray({1, 12, -5, -6, 50, 3}, 4), 12.75);
  EXPECT_EQ(max_avg_subarray({5}, 1), 5.0);
  EXPECT_EQ(max_avg_subarray({0, 4, 0, 3, 2}, 1), 4.0);
}
