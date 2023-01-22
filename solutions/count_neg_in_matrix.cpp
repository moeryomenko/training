#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <numeric>
#include <vector>

auto countNegatives(std::vector<std::vector<int>> grid) -> int {
  return std::accumulate(
      grid.begin(), grid.end(), 0,
      [end_shift = grid.front().size()](auto counter, auto vec) mutable {
        auto neg = std::partition_point(vec.cbegin(), vec.cbegin() + end_shift,
                                        [](auto n) { return n >= 0; });
        end_shift = std::distance(vec.cbegin(), neg);
        return counter + std::distance(neg, vec.cend());
      });
};

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(
        countNegatives(
            {{4, 3, 2, -1}, {3, 2, 1, -1}, {1, 1, -1, -2}, {-1, -1, -2, -3}}) ==
        8_i);
    expect(countNegatives({{5, 1, 0}, {-5, -5, -5}}) == 3_i);
    expect(countNegatives({{3, 2}, {1, 0}}) == 0_i);
    expect(countNegatives({{3, -1, -3, -3, -3},
                           {2, -2, -3, -3, -3},
                           {1, -2, -3, -3, -3},
                           {0, -3, -3, -3, -3}}) == 16_i);
  };

  return EXIT_SUCCESS;
}
