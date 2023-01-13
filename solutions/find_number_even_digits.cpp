#include <boost/ut.hpp>

#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <vector>

auto find_numbers(const std::vector<int> &nums) -> int {
  return std::count_if(nums.cbegin(), nums.cend(), [](int n) {
    return (static_cast<int>(std::log10(n)) + 1) % 2 == 0;
  });
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(find_numbers({12, 345, 2, 6, 7896}) == 2_i);
    expect(find_numbers({555, 901, 482, 1771}) == 1_i);
  };

  return EXIT_SUCCESS;
}
