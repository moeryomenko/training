#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <numeric>
#include <vector>

auto min_cost_climbing_stairs(std::vector<int> &&cost) -> int {
  auto len = cost.size();
  for (int i = 2; i < len; ++i) {
    cost[i] += std::min(cost[i - 1], cost[i - 2]);
  }
  return std::min(cost[len - 1], cost[len - 2]);
}

auto main() -> int {
  using namespace boost::ut;

  "case"_test = [] {
    expect(min_cost_climbing_stairs({10, 15, 20}) == 15_i);
    expect(min_cost_climbing_stairs({1, 100, 1, 1, 1, 100, 1, 1, 100, 1}) ==
           6_i);
  };

  return EXIT_SUCCESS;
}
