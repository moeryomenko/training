#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <numeric>
#include <vector>

auto trap(const std::vector<int> &height) -> int {
  std::vector<int> u(height.size(), 0);
  auto it = std::max_element(height.cbegin(), height.cend());
  std::inclusive_scan(height.cbegin(), std::next(it), u.begin(),
                      [](auto a, auto b) { return std::max(a, b); });
  std::inclusive_scan(height.crbegin(), std::make_reverse_iterator(it),
                      u.rbegin(),
                      [](auto a, auto b) { return std::max(a, b); });
  return std::transform_reduce(u.cbegin(), u.cend(), height.cbegin(), 0,
                               std::plus{}, std::minus{});
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(trap(std::vector{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) == 6_i);
    expect(trap(std::vector{4, 2, 0, 3, 2, 5}) == 9_i);
  };

  return EXIT_SUCCESS;
}
