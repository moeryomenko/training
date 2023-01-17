#include <boost/ut.hpp>

#include <algorithm>
#include <cstdlib>
#include <deque>
#include <functional>
#include <map>
#include <numeric>
#include <queue>
#include <set>
#include <vector>

template <typename T>
class max_heap_t
    : public std::priority_queue<T, std::vector<T>, std::less<int>> {
public:
  bool remove(const T &value) {
    auto it = std::find(this->c.begin(), this->c.end(), value);

    if (it == this->c.end()) {
      return false;
    }
    if (it == this->c.begin()) {
      // deque the top element
      this->pop();
    } else {
      // remove element and re-heap
      this->c.erase(it);
      std::make_heap(this->c.begin(), this->c.end(), this->comp);
    }
    return true;
  }
};

auto max_sliding_window_slower(const std::vector<int> &nums, int k)
    -> std::vector<int> {
  std::vector<int> res;
  res.reserve(nums.size() - k + 1);
  for (int window_begin = 0, window_end = k; window_end <= nums.size();
       ++window_begin, ++window_end) {
    auto begin = nums.cbegin() + window_begin;
    auto end = nums.cbegin() + window_end;
    res.emplace_back(*std::max_element(begin, end));
  }
  return res;
}

auto max_sliding_window_slow(const std::vector<int> &nums, int k)
    -> std::vector<int> {
  std::vector<int> res;
  res.reserve(nums.size() - k + 1);
  res.emplace_back(*std::max_element(nums.cbegin(), nums.cbegin() + k));
  for (int window_begin = 1, window_end = k + 1; window_end <= nums.size();
       ++window_begin, ++window_end) {
    auto begin = nums.cbegin() + window_begin;
    auto end = nums.cbegin() + window_end;
    auto prev_max = res.back();
    if (prev_max < *(end - 1)) {
      res.push_back(*(end - 1));
    } else if (prev_max == *(begin - 1)) {
      res.emplace_back(*std::max_element(begin, end));
    } else {
      res.push_back(res.back());
    }
  }
  return res;
}

auto max_sliding_window_max_heap(const std::vector<int> &nums, int k)
    -> std::vector<int> {
  using max_heap_t = std::priority_queue<int, std::vector<int>, std::less<int>>;
  auto max_heap = std::accumulate(nums.cbegin(), nums.cbegin() + k,
                                  max_heap_t{}, [](max_heap_t max_heap, int n) {
                                    max_heap.push(n);
                                    return max_heap;
                                  });
  std::vector<int> res{};
  res.reserve(nums.size() - k + 1);
  res.push_back(max_heap.top());

  return std::accumulate(
      nums.cbegin() + k, nums.cend(), res,
      [&max_heap, prev = nums.cbegin()](auto v, int next) mutable {
        max_heap.push(next);
        if (max_heap.top() == *prev++)
          max_heap.pop();

        v.push_back(max_heap.top());
        return v;
      });
}

auto max_sliding_window_max_heap_map(const std::vector<int> &nums, int k)
    -> std::vector<int> {
  auto max_heap =
      std::accumulate(nums.cbegin(), nums.cbegin() + k, std::map<int, int>{},
                      [](auto max_heap, int n) {
                        max_heap[n]++;
                        return max_heap;
                      });
  std::vector<int> res{};
  res.reserve(nums.size() - k + 1);
  res.push_back(max_heap.rbegin()->first);

  auto replace = [&max_heap](int out_window, int next) {
    if (out_window == next)
      return;
    if (--max_heap[out_window] == 0)
      max_heap.erase(out_window);
    max_heap[next]++;
  };

  return std::accumulate(
      nums.cbegin() + k, nums.cend(), res,
      [&max_heap, &replace, prev = nums.cbegin()](auto v, int next) mutable {
        replace(*prev++, next);
        v.push_back(max_heap.rbegin()->first);
        return v;
      });
}

auto max_sliding_window_custom_max_heap(const std::vector<int> &nums, int k)
    -> std::vector<int> {
  auto max_heap =
      std::accumulate(nums.cbegin(), nums.cbegin() + k, max_heap_t<int>{},
                      [](max_heap_t<int> max_heap, int n) {
                        max_heap.push(n);
                        return max_heap;
                      });
  std::vector<int> res{};
  res.reserve(nums.size() - k + 1);
  res.push_back(max_heap.top());

  return std::accumulate(
      nums.cbegin() + k, nums.cend(), res,
      [&max_heap, prev = nums.cbegin()](auto v, int next) mutable {
        if (int out_of_window = *prev++; out_of_window != next) {
          max_heap.remove(out_of_window);
          max_heap.push(next);
        }

        v.push_back(max_heap.top());
        return v;
      });
}

auto max_sliding_window(const std::vector<int> &nums, int k)
    -> std::vector<int> {
  // deque approach.
  std::vector<int> res;
  std::deque<int> q;
  int l = 0, r = 0;

  for (int r = 0; r < nums.size(); ++r) {
    while (!q.empty() and nums[*q.crbegin()] < nums[r])
      q.pop_back();
    q.push_back(r);

    if (l > *q.cbegin())
      q.pop_front();

    if (r + 1 >= k) {
      res.push_back(nums[*q.begin()]);
      ++l;
    }
  }

  return res;
}

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(max_sliding_window({1, 3, -1, -3, 5, 3, 6, 7}, 3) ==
           std::vector{3, 3, 5, 5, 6, 7});
    expect(max_sliding_window({1}, 1) == std::vector{1});
    expect(max_sliding_window({-7, -8, 7, 5, 7, 1, 6, 0}, 4) ==
           std::vector{7, 7, 7, 7, 7});
  };

  for (auto solution :
       std::vector<std::pair<std::string, std::function<std::vector<int>(
                                              const std::vector<int> &, int)>>>{
           {"1st approach", max_sliding_window_slower},
           {"2st approach", max_sliding_window_slow},
           {"1st approach of max_heap", max_sliding_window_max_heap},
           {"2st approach of max_heap", max_sliding_window_max_heap_map},
           {"3st approach of max_heap", max_sliding_window_custom_max_heap},
           {"queue approach", max_sliding_window},
       }) {
    ankerl::nanobench::Bench().run(solution.first, [&solution] {
      ankerl::nanobench::doNotOptimizeAway(
          solution.second({1, 3, -1, -3, 5, 3, 6, 7, -7, -8, 7, 5, 7, 1, 6, 0,
                           1, 3, -1, -3, 5, 3, 6, 7, -7, -8, 7, 5, 7, 1, 6, 0,
                           1, 3, -1, -3, 5, 3, 6, 7, -7, -8, 7, 5, 7, 1, 6, 0,
                           1, 3, -1, -3, 5, 3, 6, 7, -7, -8, 7, 5, 7, 1, 6, 0},
                          10));
    });
  }

  return EXIT_SUCCESS;
}
