#include <string_view>

#include <gtest/gtest.h>

auto backspace_cmp(std::string_view s, std::string_view t) -> bool {
  int i = s.length() - 1;
  int j = t.length() - 1;

  while (true) {
    for (int back = 0; i >= 0 && (s[i] == '#' || back > 0); --i)
      back += s[i] == '#' ? 1 : -1;
    for (int back = 0; j >= 0 && (t[j] == '#' || back > 0); --j)
      back += t[j] == '#' ? 1 : -1;

    if (i >= 0 && j >= 0 && s[i] == t[j]) {
      --i;
      --j;
    } else {
      break;
    }
  }

  return i == -1 && j == -1;
}

TEST(BackspaceStringCmp, Cases) {
  EXPECT_TRUE(backspace_cmp("ab#c", "ad#c"));
  EXPECT_TRUE(backspace_cmp("aa#b#c", "ad#c"));
  EXPECT_TRUE(backspace_cmp("ab##", "c#d#"));
}
