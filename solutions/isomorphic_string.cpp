#include <boost/ut.hpp>

#include <algorithm>
#include <array>
#include <bitset>
#include <cstdlib>
#include <map>
#include <set>
#include <string>

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

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(is_isomorphic("egg", "add"));
    expect(!is_isomorphic("foo", "bar"));
    expect(!is_isomorphic("bbbaaaba", "aaabbbba"));
    expect(!is_isomorphic("babc", "baba"));
  };

  return EXIT_SUCCESS;
}
