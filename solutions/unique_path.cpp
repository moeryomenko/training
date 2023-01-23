#include <boost/ut.hpp>

#include <cstdlib>
#include <numeric>
#include <vector>

auto uniquePaths(int m, int n) -> int {
  std::vector<int> row(n, 1);

  for (int i = 1; i < m; ++i)
    std::inclusive_scan(row.cbegin(), row.cend(), row.begin());

  return row.back();
}

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(uniquePaths(3, 7) == 28_i);
    expect(uniquePaths(3, 2) == 3_i);
  };

  return EXIT_SUCCESS;
}
