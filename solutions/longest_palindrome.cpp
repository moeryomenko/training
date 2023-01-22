#include <boost/ut.hpp>

#include <cstdlib>
#include <functional>
#include <map>
#include <numeric>
#include <string>
#include <string_view>
#include <vector>

auto longest_palindrome(std::string_view s) -> int {
  auto mp = std::accumulate(s.cbegin(), s.cend(), std::array<int, 128>{0},
                            [](auto mp, char c) {
                              mp[c]++;
                              return mp;
                            });

  int ans = std::accumulate(mp.cbegin(), mp.cend(), 0,
                            [](int ans, int k) { return ans += k - (k % 2); });

  return ans == s.size() ? ans : ans + 1;
}

auto leetcode_best_solution(std::string_view s) -> int {
  std::vector<int> freqs(128, 0);
  for (char c : s)
    ++freqs[c];
  int ans = 0;
  int odd = 0;
  for (const int freq : freqs) {
    ans += (freq % 2 == 0) ? freq : freq - 1;
    if (freq & 1)
      odd = 1;
  }
  ans += odd;
  return ans;
}

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(longest_palindrome("abccccdd") == 7_i);
    expect(longest_palindrome("a") == 1_i);
  };

  for (auto solution : std::vector<
           std::pair<std::string, std::function<int(std::string_view)>>>{
           {"my solution", longest_palindrome},
           {"best leetcode solution", leetcode_best_solution},
       }) {
    ankerl::nanobench::Bench().run(solution.first, [&solution] {
      ankerl::nanobench::doNotOptimizeAway(
          solution.second("asdkfjaskdjfkasjdfjkhasfuqoiuncasndfojhdrguqoeruirb"
                          "ghrbtqejnsdfkjashdfj"));
    });
  }

  return EXIT_SUCCESS;
}
