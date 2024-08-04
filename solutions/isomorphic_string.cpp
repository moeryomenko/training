#include <algorithm>
#include <array>
#include <bitset>
#include <string>

#include <gtest/gtest.h>

auto is_isomorphic(std::string s, std::string t) -> bool {
  return std::equal(s.cbegin(), s.cend(), t.cbegin(), t.cend(),
                    [translation = std::array<char, 26>{0},
                     visited = std::bitset<32>{0}](char s, char t) mutable {
                      if (translation[s - 'a'] == 0 && !visited.test(t - 'a')) {
                        visited.set(t - 'a');
                        translation[s - 'a'] = t;
                        return true;
                      }

                      return translation[s - 'a'] == t;
                    });
}

TEST(Isomorphic, Cases) {
  EXPECT_TRUE(is_isomorphic("egg", "add"));
  EXPECT_FALSE(is_isomorphic("foo", "bar"));
  EXPECT_FALSE(is_isomorphic("bbbaaaba", "aaabbbba"));
  EXPECT_FALSE(is_isomorphic("babc", "baba"));
}
