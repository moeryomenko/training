#include <numeric>
#include <string_view>
#include <vector>

#include <gtest/gtest.h>

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

TEST(LongestPalindrome, Cases) {
  EXPECT_EQ(longest_palindrome("abccccdd"), 7);
  EXPECT_EQ(longest_palindrome("a"), 1);
}
