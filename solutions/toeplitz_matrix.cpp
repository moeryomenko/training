#include <algorithm>
#include <vector>

#include <gtest/gtest.h>

auto is_toeplitz_matrix(std::vector<std::vector<int>> matrix) -> bool {
  return std::all_of(matrix.cbegin() + 1, matrix.cend(),
                     [prev_row = matrix.front()](auto row) mutable {
                       std::shift_right(prev_row.begin(), prev_row.end(), 1);
                       *prev_row.begin() = row.front();
                       return std::equal(prev_row.cbegin(), prev_row.cend(),
                                         row.cbegin(), row.cend());
                     });
}

TEST(ToeplitzMatrix, Cases) {
  EXPECT_TRUE(is_toeplitz_matrix(
      std::vector<std::vector<int>>{{1, 2, 3, 4}, {5, 1, 2, 3}, {9, 5, 1, 2}}));
  EXPECT_FALSE(
      is_toeplitz_matrix(std::vector<std::vector<int>>{{1, 2}, {2, 2}}));
}
