#include <algorithm>
#include <boost/ut.hpp>

#include <cstdlib>
#include <numeric>
#include <stack>
#include <utility>
#include <vector>

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
