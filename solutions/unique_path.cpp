#include <gtest/gtest.h>
#include <numeric>
#include <vector>

auto uniquePaths(int m, int n) -> int {
  std::vector<int> row(n, 1);

  for (int i = 1; i < m; ++i)
    std::inclusive_scan(row.cbegin(), row.cend(), row.begin());

  return row.back();
}

TEST(UniquePaths, Cases) {
  EXPECT_EQ(uniquePaths(3, 7), 28);
  EXPECT_EQ(uniquePaths(3, 2), 3);
}
