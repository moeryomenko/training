#include <boost/ut.hpp>

#include <vector>

auto gray_code(int n) -> std::vector<int> {
  std::vector<int> code(1 << n);

  int last = 1 << (n - 1);

  int half_index = (1 << n) / 2;
  int last_index = (1 << n) - 1;

  for (int i = 0; i < half_index; ++i) {
    int val = i ^ (i >> 1);
    code[i] = val;
    code[last_index - i] = last + val;
  }

  return code;
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(gray_code(2) == std::vector{0, 1, 3, 2});
    expect(gray_code(1) == std::vector{0, 1});
    expect(gray_code(3) == std::vector{0, 1, 3, 2, 6, 7, 5, 4});
    expect(gray_code(5) == std::vector{0,  1,  3,  2,  6,  7,  5,  4,
                                       12, 13, 15, 14, 10, 11, 9,  8,
                                       24, 25, 27, 26, 30, 31, 29, 28,
                                       20, 21, 23, 22, 18, 19, 17, 16});
  };

  return 0;
}
