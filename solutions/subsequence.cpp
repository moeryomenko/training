#include <algorithm>
#include <cstdlib>
#include <string_view>

#include <gtest/gtest.h>

auto is_subsequence(std::string_view s, std::string_view t) -> bool {
  return s.length() ==
         std::count_if(t.cbegin(), t.cend(), [it = s.cbegin()](char t) mutable {
           if (*it == t) {
             ++it;
             return true;
           }
           return false;
         });
}

TEST(Subsequence, Cases) {
  EXPECT_TRUE(is_subsequence("abc", "ahbgdc"));
  EXPECT_FALSE(is_subsequence("axc", "ahbgdc"));
}
