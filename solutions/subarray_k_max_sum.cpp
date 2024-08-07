#include <numeric>
#include <vector>

#include <gtest/gtest.h>

auto max_subsequence(const std::vector<int> &nums, int k) -> int {
  // auto __sum = std::accumulate(nums.cbegin(), nums.cbegin() + k, 0);

  // auto __end = nums.cend();
  // for (auto __first = nums.cbegin(), __next = nums.cbegin() + k;
  //      __next != __end; ++__next, ++__first) {
  //   auto __temp = __sum + *__next - *__first;
  //   if (__temp > __sum) {
  //     __sum = __temp;
  //   }
  // }

  // auto sum = std::accumulate(nums.cbegin(), nums.cbegin() + k, 0);
  // std::for_each(nums.cbegin() + k, nums.cend(),
  //               [&sum, first = nums.cbegin()](int a) mutable {
  //                 auto temp = sum + a - *first;
  //                 if (temp > sum) {
  //                   sum = temp;
  //                 }
  //                 first++;
  //               });

  return std::accumulate(nums.cbegin() + k, nums.cend(),
                         std::accumulate(nums.cbegin(), nums.cbegin() + k, 0),
                         [prev = nums.cbegin()](int sum, int n) mutable {
                           return std::max(sum + n - *prev++, sum);
                         });
}

TEST(MaxSubarrayKMaxSum, Cases) {
  EXPECT_EQ(max_subsequence({2, 1, 3, 3}, 2), 6);   // sum([3, 3]) = 6
  EXPECT_EQ(max_subsequence({-1, -1, 3, 4}, 3), 6); // sum([-1, 3, 4]) = 6
}
