#include <algorithm>
#include <cstdlib>
#include <functional>
#include <numeric>
#include <vector>

#include <gtest/gtest.h>

auto trap(const std::vector<int> &height) -> int {
  std::vector<int> u(height.size(), 0);
  auto it = std::max_element(height.cbegin(), height.cend());
  auto max = [](auto a, auto b) { return std::max(a, b); };
  std::inclusive_scan(height.cbegin(), std::next(it), u.begin(), max);
  std::inclusive_scan(height.crbegin(), std::make_reverse_iterator(it),
                      u.rbegin(), max);
  return std::transform_reduce(u.cbegin(), u.cend(), height.cbegin(), 0,
                               std::plus{}, std::minus{});
}

auto trap2(const std::vector<int> &height) -> int {
  auto it = std::max_element(height.cbegin(), height.cend());
  auto sum = [](auto begin, auto end, auto init) {
    return std::accumulate(begin, end, 0, [max = init](int sum, int n) mutable {
      max = std::max(max, n);
      return (sum += max - n);
    });
  };
  return sum(height.cbegin(), it, height.front()) +
         sum(height.crbegin(), std::make_reverse_iterator(it), height.back());
}

TEST(TrapRainWater, Cases) {
  // 0, 1, 1, 2, 2, 2, 2, 3, 2, 1, 2, 1
  // 0, 1, 1, 2, 2, 2, 2, 3, 2, 2, 2, 1
  // 0, 0, 1, 0, 1, 2, 1, 0, 0, 1, 0, 0 = 6
  EXPECT_EQ(trap(std::vector{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}), 6);
  // 4, 4, 4, 4, 4, 5
  // 0, 2, 4, 1, 2, 0 = 9
  EXPECT_EQ(trap(std::vector{4, 2, 0, 3, 2, 5}), 9);
  EXPECT_EQ(trap2(std::vector{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}), 6);
  EXPECT_EQ(trap2(std::vector{4, 2, 0, 3, 2, 5}), 9);
}
