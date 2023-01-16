#include <boost/ut.hpp>

#include <cstdlib>
#include <set>
#include <vector>

auto find_k_largets(const std::vector<int> &nums, int k) -> int {
  std::multiset<int> res;
  res.insert(nums.begin(), nums.end());
  auto it = res.rbegin();
  for (int i = 0; i < k - 1; ++i)
    it++;
  return *it;
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] { expect(find_k_largets({3, 2, 1, 5, 6, 4}, 2) == 5_i); };

  return EXIT_SUCCESS;
}
