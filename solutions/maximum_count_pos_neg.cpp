#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <ranges>
#include <vector>

auto maximumCount(const std::vector<int> &nums) -> int {
  auto [last_neg, first_pos] = std::equal_range(nums.cbegin(), nums.cend(), 0);
  return std::max(std::distance(nums.cbegin(), last_neg),
                  std::distance(first_pos, nums.cend()));
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(maximumCount({-2, -1, -1, 1, 2, 3}) == 3_i);
    expect(maximumCount({-3, -2, -1, 0, 0, 1, 2}) == 3_i);
    expect(maximumCount({5, 20, 66, 1314}) == 4_i);
  };

  return EXIT_SUCCESS;
}
