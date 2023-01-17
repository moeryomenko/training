#include <boost/ut.hpp>

#include <cmath>
#include <float.h>

constexpr auto root(double n) -> double {
  double x = n;
  double y = 1;
  double e = DBL_MIN;
  while (x - y > e) {
    x = (x + y) / 2;
    y = n / x;
  }
  return x;
}

constexpr auto root_5 = root(5);
constexpr auto gold_ratio = (1.f + root_5) / 2;
constexpr auto revers_gold_ratio = (1.f - root_5) / 2;

auto climb_stairs(int n) -> int {
  if (n < 0)
    return 0;
  if (n == 0)
    return 1;
  return std::round(
      (std::pow(gold_ratio, n + 1) - std::pow(revers_gold_ratio, n + 1)) /
      root_5);
}

#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

auto main() -> int {
  using namespace boost::ut;

  "cases"_test = [] {
    expect(climb_stairs(2) == 2_i);
    expect(climb_stairs(3) == 3_i);
    expect(climb_stairs(4) == 5_i);
    expect(climb_stairs(35) == 14930352_i);
  };

  ankerl::nanobench::Bench().run("constexpr solution", [] {
    ankerl::nanobench::doNotOptimizeAway(climb_stairs(100));
  });

  return 0;
}
