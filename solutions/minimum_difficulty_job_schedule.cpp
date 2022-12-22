#include <boost/ut.hpp>

#include <algorithm>
#include <iostream>
#include <limits>
#include <stack>
#include <vector>

int min_difficulty(const std::vector<int> &jobDifficulty, int d) {
  if (jobDifficulty.size() < d)
    return -1;

  std::vector<int> dp(jobDifficulty.size());
  std::stack<int> st;

  int max_val = std::numeric_limits<int>::min();
  for (int i = 0; i < jobDifficulty.size(); i++) {
    max_val = std::max(max_val, jobDifficulty[i]);
    dp[i] = max_val;
  }

  std::vector<int> temp(jobDifficulty.size());

  for (int cur_d = 2; cur_d <= d; cur_d++) {
    // flush temp vector.
    std::fill(temp.begin(), temp.end(), std::numeric_limits<int>::max());

    if (!st.empty())
      st.pop();

    for (int j = cur_d - 1; j < jobDifficulty.size(); j++) {
      int cur_val = jobDifficulty[j];

      temp[j] = dp[j - 1] + cur_val;

      while (!st.empty() && jobDifficulty[st.top()] <= cur_val) {
        temp[j] = std::min(temp[j],
                           temp[st.top()] - jobDifficulty[st.top()] + cur_val);
        st.pop();
      }

      if (!st.empty()) {
        temp[j] = std::min(temp[j], temp[st.top()]);
      }

      st.push(j);
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
