#include <vector>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

auto two_sum(const std::vector<int> &nums, int target) -> std::vector<int> {
  for (int i = 0; i < nums.size(); ++i)
    for (int j = i + 1; j < nums.size(); ++j)
      if (nums[i] + nums[j] == target)
        return {i, j};
  return {-1, -1};
}

TEST(TwoSum, Cases) {
  ASSERT_THAT(two_sum(std::vector{2, 7, 11, 15}, 9),
              testing::ElementsAre(0, 1));
  ASSERT_THAT(two_sum(std::vector{3, 2, 4}, 6), testing::ElementsAre(1, 2));
  ASSERT_THAT(two_sum(std::vector{3, 3}, 6), testing::ElementsAre(0, 1));
}
