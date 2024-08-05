#include <algorithm>
#include <vector>

#include <gtest/gtest.h>

template <typename F> void bulk_foreach(std::vector<int> vec, int bulk, F f) {
  int n = 0, size = vec.size();
  auto it = vec.begin();
  while (it != vec.end()) {
    auto step = n + bulk > size ? size - n : bulk;
    auto last = it + step;
    f(std::vector<int>(it, last));
    it += step;
    n += step;
  }
}

template <class InputIt1, class InputIt2>
void accamulate_work(InputIt1 begin1, InputIt1 end1, InputIt2 begin2,
                     InputIt2 end2) {
  auto it1 = begin1;
  auto it2 = begin2;
  for (; it1 != end1 && it2 != end2; ++it2) {
    *it1 += *it2;
    if (it1 + 1 == end1)
      break;
    if (*it1 >= *(it1 + 1))
      ++it1;
  }
}

auto queueTime(std::vector<int> customers, int n) -> long {
  int len = customers.size();
  if (len == 0)
    return 0;

  if (len < n)
    return *std::max_element(customers.begin(), customers.end());

  std::vector<long> workers(n, 0);

  bulk_foreach(customers, n, [&workers](const std::vector<int> &vec) {
    accamulate_work(workers.begin(), workers.end(), vec.begin(), vec.end());
    std::stable_sort(workers.begin(), workers.end());
  });

  return *std::max_element(workers.begin(), workers.end());
}

TEST(QueueTime, Cases) {
  EXPECT_EQ(queueTime({1, 2, 3, 4, 5}, 100), 5);
  EXPECT_EQ(queueTime({}, 1), 0);
  EXPECT_EQ(queueTime({2, 2, 3, 3, 4, 4}, 2), 9);
  EXPECT_EQ(queueTime({1, 2, 3, 4}, 1), 10);
  EXPECT_EQ(queueTime({2, 3, 10}, 2), 12);
  EXPECT_EQ(queueTime({10, 2, 3, 3}, 2), 10);
  EXPECT_EQ(queueTime({12, 2, 2, 10, 9, 1, 1}, 3), 13);
}
