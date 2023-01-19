#include <algorithm>
#include <boost/ut.hpp>

#include <cstdlib>
#include <vector>

auto search(const std::vector<int> &nums, int target) -> int {
  auto it = std::lower_bound(nums.cbegin(), nums.cend(), target);

  return it != nums.cend() && *it == target ? std::distance(nums.cbegin(), it)
                                            : -1;
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(search({-1, 0, 3, 5, 9, 12}, 9) == 4_i);
    expect(search({-1, 0, 3, 5, 9, 12}, 2) == -1_i);
  };

  return EXIT_SUCCESS;
}
