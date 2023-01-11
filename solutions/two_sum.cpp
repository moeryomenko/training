#include <boost/ut.hpp>

#include <vector>

auto two_sum(const std::vector<int> &nums, int target) -> std::vector<int> {
  for (int i = 0; i < nums.size(); ++i)
    for (int j = i + 1; j < nums.size(); ++j)
      if (nums[i] + nums[j] == target)
        return {i, j};
  return {-1, -1};
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(two_sum(std::vector{2, 7, 11, 15}, 9) == std::vector{0, 1});
    expect(two_sum(std::vector{3, 2, 4}, 6) == std::vector{1, 2});
    expect(two_sum(std::vector{3, 3}, 6) == std::vector{0, 1});
  };

  return 0;
}
