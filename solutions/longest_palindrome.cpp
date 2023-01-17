#include <boost/ut.hpp>

#include <cstdlib>
#include <map>
#include <numeric>
#include <string_view>

auto longest_palindrome(std::string_view s) -> int {
  auto mp = std::accumulate(s.cbegin(), s.cend(), std::array<int, 128>{0},
                            [](auto mp, char c) {
                              mp[c]++;
                              return mp;
                            });

  int ans = std::accumulate(mp.cbegin(), mp.cend(), 0, [](int ans, int k) {
    ans += k - (k % 2);
    return ans;
  });

  return ans == s.size() ? ans : ans + 1;
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(longest_palindrome("abccccdd") == 7_i);
    expect(longest_palindrome("a") == 1_i);
  };

  return EXIT_SUCCESS;
}
