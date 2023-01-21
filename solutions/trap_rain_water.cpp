#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <numeric>
#include <vector>

auto trap(const std::vector<int> &height) -> int {
  std::vector<int> u(height.size(), 0);
  auto it = std::max_element(height.cbegin(), height.cend());
  auto max = [](auto a, auto b) { return std::max(a, b); };
  std::inclusive_scan(height.cbegin(), std::next(it), u.begin(), max);
  std::inclusive_scan(height.crbegin(), std::make_reverse_iterator(it),
                      u.rbegin(), max);
  return std::transform_reduce(u.cbegin(), u.cend(), height.cbegin(), 0,
                               std::plus{}, std::minus{});
}

auto trap2(const std::vector<int> &height) -> int {
  auto it = std::max_element(height.cbegin(), height.cend());
  auto sum = [](auto begin, auto end, auto init) {
    return std::accumulate(begin, end, 0, [max = init](int sum, int n) mutable {
      max = std::max(max, n);
      return (sum += max - n);
    });
  };
  return sum(height.cbegin(), it, height.front()) +
         sum(height.crbegin(), std::make_reverse_iterator(it), height.back());
}

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(trap(std::vector{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) == 6_i);
    // 0, 1, 1, 2, 2, 2, 2, 3, 2, 1, 2, 1
    // 0, 1, 1, 2, 2, 2, 2, 3, 2, 2, 2, 1
    // 0, 0, 1, 0, 1, 2, 1, 0, 0, 1, 0, 0 = 6
    expect(trap(std::vector{4, 2, 0, 3, 2, 5}) == 9_i);
    // 4, 4, 4, 4, 4, 5
    // 0, 2, 4, 1, 2, 0 = 9
    expect(trap2(std::vector{0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}) == 6_i);
    expect(trap2(std::vector{4, 2, 0, 3, 2, 5}) == 9_i);
  };

  for (auto solution :
       std::vector<std::pair<std::string,
                             std::function<int(const std::vector<int> &)>>>{
           {"1st approach", trap},
           {"2st approach", trap2},
       }) {
    ankerl::nanobench::Bench().run(solution.first, [&solution] {
      ankerl::nanobench::doNotOptimizeAway(
          solution.second({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}));
    });
  }

  return EXIT_SUCCESS;
}
