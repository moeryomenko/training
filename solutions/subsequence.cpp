#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <string_view>

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

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(is_subsequence("abc", "ahbgdc"));
    expect(!is_subsequence("axc", "ahbgdc"));
  };

  return EXIT_SUCCESS;
}
