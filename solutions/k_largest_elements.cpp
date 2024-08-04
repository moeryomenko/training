#include <set>
#include <vector>

#include <gtest/gtest.h>

auto find_k_largets(const std::vector<int> &nums, int k) -> int {
  std::multiset<int> res;
  res.insert(nums.begin(), nums.end());
  auto it = res.rbegin();
  for (int i = 0; i < k - 1; ++i)
    it++;
  return *it;
}

TEST(FindKLargest, Cases) {
  EXPECT_EQ(find_k_largets({3, 2, 1, 5, 6, 4}, 2), 5);
}
