#include <algorithm>
#include <vector>

#include <gtest/gtest.h>

auto min_cost_climbing_stairs(std::vector<int> &&cost) -> int {
  auto len = cost.size();
  for (int i = 2; i < len; ++i) {
    cost[i] += std::min(cost[i - 1], cost[i - 2]);
  }
  return std::min(cost[len - 1], cost[len - 2]);
}

TEST(MinCostClimbingStairs, Cases) {
  EXPECT_EQ(min_cost_climbing_stairs({10, 15, 20}), 15);
  EXPECT_EQ(min_cost_climbing_stairs({1, 100, 1, 1, 1, 100, 1, 1, 100, 1}), 6);
}
