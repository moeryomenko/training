#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <numeric>
#include <vector>

auto running_sum(std::vector<int> &&nums) -> std::vector<int> {
  std::transform(nums.cbegin() + 1, nums.cend(), nums.begin() + 1,
                 [sum = nums[0]](int n) mutable { return (sum += n); });
  return nums;
}

auto running_sum2(std::vector<int> &&nums) -> std::vector<int> {
  std::inclusive_scan(nums.cbegin(), nums.cend(), nums.begin());
  return nums;
}

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(running_sum(std::vector{1, 2, 3, 4}) == std::vector{1, 3, 6, 10});
    expect(running_sum(std::vector{1, 1, 1, 1, 1}) ==
           std::vector{1, 2, 3, 4, 5});
    expect(running_sum(std::vector{3, 1, 2, 10, 1}) ==
           std::vector{3, 4, 6, 16, 17});
    expect(running_sum2(std::vector{1, 2, 3, 4}) == std::vector{1, 3, 6, 10});
    expect(running_sum2(std::vector{1, 1, 1, 1, 1}) ==
           std::vector{1, 2, 3, 4, 5});
    expect(running_sum2(std::vector{3, 1, 2, 10, 1}) ==
           std::vector{3, 4, 6, 16, 17});
  };

  for (auto solution : std::vector<std::pair<
           std::string, std::function<std::vector<int>(std::vector<int> &&)>>>{
           {"1st approach", running_sum},
           {"2st approach", running_sum2},
       }) {
    ankerl::nanobench::Bench().run(solution.first, [&solution] {
      ankerl::nanobench::doNotOptimizeAway(
          solution.second({0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1}));
    });
  }

  return EXIT_SUCCESS;
}
