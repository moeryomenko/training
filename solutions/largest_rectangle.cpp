#include <algorithm>
#include <numeric>
#include <utility>
#include <vector>

#include <gtest/gtest.h>

auto largest_rectangle(std::vector<int> heights) -> int {
  std::vector<std::pair<int, int>> stack;
  heights.push_back(0);
  return std::accumulate(heights.cbegin(), heights.cend(), 0,
                         [&stack, i = 0](auto max, auto h) mutable {
                           int start = i;
                           while (!stack.empty() && stack.back().second > h) {
                             auto [index, height] = stack.back();
                             stack.pop_back();

                             max = std::max(max, height * (i - index));
                             start = index;
                           }
                           stack.push_back({start, h});
                           ++i;

                           return max;
                         });
}

auto maximal_rectangle(const std::vector<std::vector<char>> &matrix) -> int {
  return std::accumulate(matrix.cbegin(), matrix.cend(), 0,
                         [row = std::vector(matrix.front().size(), 0)](
                             auto max, auto chars) mutable {
                           std::transform(row.cbegin(), row.cend(), row.begin(),
                                          [v = chars.begin()](int n) mutable {
                                            return *v++ == '1' ? n + 1 : 0;
                                          });
                           return std::max(max, largest_rectangle(row));
                         });
}

TEST(LargestRectangle, Cases) {
  EXPECT_EQ(largest_rectangle({2, 1, 5, 6, 2, 3}), 10);
}

TEST(MaximalRectangle, Cases) {
  EXPECT_EQ(maximal_rectangle({{'1', '0', '1', '0', '0'},
                               {'1', '0', '1', '1', '1'},
                               {'1', '1', '1', '1', '1'},
                               {'1', '0', '0', '1', '0'}}),
            6);
  EXPECT_EQ(maximal_rectangle({{'1', '0', '1', '0', '0'},
                               {'1', '0', '1', '1', '1'},
                               {'1', '1', '1', '1', '1'},
                               {'1', '1', '1', '1', '1'}}),
            10);
  EXPECT_EQ(maximal_rectangle({{'0'}}), 0);
}
