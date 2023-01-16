#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <iterator>
#include <numeric>
#include <vector>

auto max_subsequence(const std::vector<int> &nums, int k) -> std::vector<int> {
  std::vector<std::pair<int, int>> temp;
  temp.reserve(nums.size());
  std::transform(nums.cbegin(), nums.cend(), std::back_inserter(temp),
                 [i = 0](int n) mutable {
                   return std::pair{n, i++};
                 });

  std::sort(temp.begin(), temp.end());

  // remove elements.
  temp.erase(temp.begin(), temp.begin() + (temp.size() - k));

  std::sort(temp.begin(), temp.end(),
            [](auto a, auto b) { return a.second < b.second; });

  std::vector<int> res;
  res.reserve(temp.size());
  std::transform(temp.cbegin(), temp.cend(), std::back_inserter(res),
                 [](auto e) { return e.first; });
  return res;
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(max_subsequence({2, 1, 3, 3}, 2) == std::vector{3, 3});
    expect(max_subsequence({-1, -2, 3, 4}, 3) == std::vector{-1, 3, 4});
  };

  return EXIT_SUCCESS;
}
