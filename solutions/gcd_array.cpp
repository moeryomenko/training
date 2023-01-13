#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <numeric>
#include <vector>

auto find_gcd(const std::vector<int> &nums) -> int {
  const auto [min, max] = std::minmax_element(nums.cbegin(), nums.cend());
  return std::gcd(*min, *max);
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(find_gcd({2, 5, 6, 9, 10}) == 2_i);
    expect(find_gcd({7, 5, 6, 8, 3}) == 1_i);
    expect(find_gcd({3, 3}) == 3_i);
  };

  return EXIT_SUCCESS;
}
