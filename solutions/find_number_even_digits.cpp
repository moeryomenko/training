#include <algorithm>
#include <cmath>
#include <vector>

#include <gtest/gtest.h>

auto find_numbers(const std::vector<int> &nums) -> int {
  return std::count_if(nums.cbegin(), nums.cend(), [](int n) {
    return (static_cast<int>(std::log10(n)) + 1) % 2 == 0;
  });
}

TEST(FindNumbersEvenDigist, Cases) {
  EXPECT_EQ(find_numbers({12, 345, 2, 6, 7896}), 2);
  EXPECT_EQ(find_numbers({555, 901, 482, 1771}), 1);
}
