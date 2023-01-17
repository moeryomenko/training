#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <iostream>
#include <iterator>
#include <numeric>
#include <set>
#include <vector>

auto find_by_order(const std::multiset<long long> &s, int k) -> long long {
  for (int i = 0; int n : s) {
    if (i == k)
      return n;
    i++;
  }
  return *s.crbegin();
}

auto order_of_key(const std::multiset<long long> &s, long long n) -> long long {
  return std::distance(s.cbegin(), std::lower_bound(s.cbegin(), s.cend(), n));
}

auto median_sliding_window(const std::vector<int> &nums, int k)
    -> std::vector<double> {
  std::multiset<long long> s;
  s.insert(nums.cbegin(), nums.cbegin() + k);

  std::vector<double> res;
  if (k & 1) {
    res.push_back(find_by_order(s, k / 2));

    for (int i = 0; i < nums.size() - k; ++i) {
      s.erase(find_by_order(s, order_of_key(s, nums[i])));

      s.insert(nums[i + k]);

      res.push_back(find_by_order(s, k / 2));
    }
  } else {
    res.push_back(static_cast<double>(find_by_order(s, (k + 1) / 2 - 1) +
                                      find_by_order(s, k / 2)) /
                  2);

    for (int i = 0; i < nums.size() - k; ++i) {
      s.erase(s.find(nums[i]));

      s.insert(nums[i + k]);

      auto l = find_by_order(s, (k + 1) / 2 - 1);
      auto r = find_by_order(s, (k / 2));
      res.push_back(static_cast<double>(l + r) / 2);
    }
  }
  return res;
}

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

auto main() -> int {
  using namespace boost::ut;

  "find_by_order/key"_test = [] {
    std::multiset<long long> s;
    s.insert(1);
    s.insert(3);
    s.insert(5);
    s.insert(7);
    s.insert(9);

    expect(order_of_key(s, 5) == 2_i);
    expect(find_by_order(s, 4) == 9_i);
  };

  "cases"_test = [] {
    expect(median_sliding_window({1, 3, -1, -3, 5, 3, 6, 7}, 3) ==
           std::vector<double>{1.00000, -1.00000, -1.00000, 3.00000, 5.00000,
                               6.00000});
    expect(median_sliding_window({5, 2, 2, 7, 3, 7, 9, 0, 2, 3}, 9) ==
           std::vector{3.0, 3.0});
    expect(median_sliding_window({5, 5, 8, 1, 4, 7, 1, 3, 8, 4}, 8) ==
           // 1, 1, 3, 4, 5, 5, 7, 8  => 4.5
           // 1, 1, 3, 4, 5, 7, 8, 8  => 4.5
           // 1, 1, 3, 4, 4, 7, 8, 8  => 4.5
           std::vector{4.5, 4.5, 4.0});
  };

  ankerl::nanobench::Bench().run("1st solution", [] {
    ankerl::nanobench::doNotOptimizeAway(
        median_sliding_window({5, 2, 2, 7, 3, 7, 9, 0, 2, 3, 5, 2, 2, 7, 3,
                               7, 9, 0, 2, 3, 5, 5, 8, 1, 4, 7, 1, 3, 8, 4},
                              9));
  });

  return EXIT_SUCCESS;
}
