#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

auto running_sum(std::vector<int> &&nums) -> std::vector<int> {
  std::transform(nums.cbegin() + 1, nums.cend(), nums.begin() + 1,
                 [sum = nums[0]](int n) mutable { return (sum += n); });
  return nums;
}

auto running_sum2(std::vector<int> &&nums) -> std::vector<int> {
  std::inclusive_scan(nums.cbegin(), nums.cend(), nums.begin());
  return nums;
}

TEST(RunningSum, Cases) {
  ASSERT_THAT(running_sum(std::vector{1, 2, 3, 4}),
              testing::ElementsAre(1, 3, 6, 10));
  ASSERT_THAT(running_sum(std::vector{1, 1, 1, 1, 1}),
              testing::ElementsAre(1, 2, 3, 4, 5));
  ASSERT_THAT(running_sum(std::vector{3, 1, 2, 10, 1}),
              testing::ElementsAre(3, 4, 6, 16, 17));
  ASSERT_THAT(running_sum2(std::vector{1, 2, 3, 4}),
              testing::ElementsAre(1, 3, 6, 10));
  ASSERT_THAT(running_sum2(std::vector{1, 1, 1, 1, 1}),
              testing::ElementsAre(1, 2, 3, 4, 5));
  ASSERT_THAT(running_sum2(std::vector{3, 1, 2, 10, 1}),
              testing::ElementsAre(3, 4, 6, 16, 17));
}
