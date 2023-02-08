#include <boost/ut.hpp>

#include <algorithm>
#include <iostream>
#include <limits>
#include <numeric>
#include <stack>
#include <vector>

int min_difficulty(const std::vector<int> &jobDifficulty, int d) {
  if (jobDifficulty.size() < d)
    return -1;

  std::vector<int> dp(jobDifficulty.size());
  std::vector<int> st;
  st.reserve(jobDifficulty.size());

  std::inclusive_scan(
      jobDifficulty.cbegin(), jobDifficulty.cend(), dp.begin(),
      [](auto a, auto b) { return std::max(a, b); },
      std::numeric_limits<int>::min());

  std::vector<int> temp(jobDifficulty.size());

  for (int cur_d = 2; cur_d <= d; cur_d++) {
    // flush temp vector.
    std::fill(temp.begin(), temp.end(), std::numeric_limits<int>::max());

    st.clear();

    for (int j = cur_d - 1; j < jobDifficulty.size(); j++) {
      int cur_val = jobDifficulty[j];

      temp[j] = dp[j - 1] + cur_val;

      while (!st.empty() && jobDifficulty[st.back()] <= cur_val) {
        temp[j] = std::min(temp[j], temp[st.back()] - jobDifficulty[st.back()] +
                                        cur_val);
        st.pop_back();
      }

      if (!st.empty()) {
        temp[j] = std::min(temp[j], temp[st.back()]);
      }

      st.push_back(j);
    }

    dp = temp;
  }

  return dp.back();
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(min_difficulty({7, 1, 7, 1, 7, 1}, 3) == 15_i);
    expect(min_difficulty({6, 5, 4, 3, 2, 1}, 2) == 7_i);
    expect(min_difficulty({9, 9, 9}, 4) == -1_i);
    expect(min_difficulty({1, 1, 1}, 3) == 3_i);
  };
}
