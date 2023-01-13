#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <vector>

auto running_sum(std::vector<int> &&nums) -> std::vector<int> {
  std::transform(nums.cbegin() + 1, nums.cend(), nums.begin() + 1,
                 [sum = nums[0]](int n) mutable { return (sum += n); });
  return nums;
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(running_sum(std::vector{1, 2, 3, 4}) == std::vector{1, 3, 6, 10});
    expect(running_sum(std::vector{1, 1, 1, 1, 1}) ==
           std::vector{1, 2, 3, 4, 5});
    expect(running_sum(std::vector{3, 1, 2, 10, 1}) ==
           std::vector{3, 4, 6, 16, 17});
  };

  return EXIT_SUCCESS;
}
