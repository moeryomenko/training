#include <algorithm>
#include <bitset>

#include <gtest/gtest.h>

auto lengthOfLongestSubstring(std::string s) -> int {
  if (s.length() == 0)
    return 0;

  int n = s.length();
  std::bitset<256> st;
  int len = 1;
  st.set(s[0]);
  int maxLen = 0;

  for (int i = 1; i < n;) {
    if (s[i] != s[i - 1] && !st.test(s[i])) {
      st.set(s[i]);
      len++;
      i++;
      maxLen = std::max(maxLen, len);
    } else {
      if (len == 1) {
        i++;
      } else {
        st.reset();
        i = i - len + 1;
        len = 0;
      }
    }
  }
  return std::max(maxLen, len);
}

TEST(LengthOfLongestSubstring, Cases) {
  EXPECT_EQ(lengthOfLongestSubstring("abcabcbb"), 3);
  EXPECT_EQ(lengthOfLongestSubstring("bbbb"), 1);
  EXPECT_EQ(lengthOfLongestSubstring("pwwkew"), 3);
  EXPECT_EQ(lengthOfLongestSubstring(" "), 1);
}
