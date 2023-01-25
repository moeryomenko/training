#include <algorithm>
#include <boost/ut.hpp>

#include <cstdlib>
#include <numeric>
#include <stack>
#include <utility>
#include <vector>

auto largest_rectangle(const std::vector<int> &heights) -> int {
  std::vector<std::pair<int, int>> stack;

  int len = heights.size();

  int max_area = 0;
  for (int i = 0; auto h : heights) {
    int start = i;
    while (!stack.empty() && stack.back().second > h) {
      auto [index, height] = stack.back();
      stack.pop_back();

      max_area = std::max(max_area, height * (i - index));
      start = index;
    }
    stack.push_back({start, h});
    ++i;
  }

  return std::accumulate(stack.cbegin(), stack.cend(), max_area,
                         [&len](int max, auto pair) {
                           auto [i, h] = pair;
                           return std::max(max, h * (len - i));
                         });
}

auto maximal_rectangle(const std::vector<std::vector<char>> &matrix) -> int {
  std::vector<std::vector<int>> dp(matrix.size());
  std::inclusive_scan(
      matrix.cbegin(), matrix.cend(), dp.begin(),
      [](std::vector<int> prev_row, std::vector<char> row) {
        std::transform(prev_row.cbegin(), prev_row.cend(), prev_row.begin(),
                       [v = row.begin()](int n) mutable {
                         return *v++ == '1' ? n + 1 : 0;
                       });
        return prev_row;
      },
      std::vector<int>(matrix.front().size(), 0));
  return std::accumulate(dp.cbegin(), dp.cend(), 0, [](int max, auto heights) {
    return std::max(max, largest_rectangle(heights));
  });
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(largest_rectangle({2, 1, 5, 6, 2, 3}) == 10_i);
    expect(maximal_rectangle({{'1', '0', '1', '0', '0'},
                              {'1', '0', '1', '1', '1'},
                              {'1', '1', '1', '1', '1'},
                              {'1', '0', '0', '1', '0'}}) == 6_i);
    expect(maximal_rectangle({{'1', '0', '1', '0', '0'},
                              {'1', '0', '1', '1', '1'},
                              {'1', '1', '1', '1', '1'},
                              {'1', '1', '1', '1', '1'}}) == 10_i);
    expect(maximal_rectangle({{'0'}}) == 0_i);
  };

  return EXIT_SUCCESS;
}
