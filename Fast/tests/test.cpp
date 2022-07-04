#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

#include "../include/arg_parse.h"
#include "../include/field.h"
#include "../include/grid.h"
#include "../include/repeats.h"
#include "../include/size.h"

BOOST_AUTO_TEST_CASE(test_size) {
  int n = 20;
  int m = 30;
  Size sz = Size(n, m);
  BOOST_REQUIRE(sz.n == n && sz.m == m);
}

BOOST_AUTO_TEST_CASE(test_repeats) {
  int n = 30;
  Repeats r = Repeats(n);
  BOOST_REQUIRE(r.rep == n);
}

BOOST_AUTO_TEST_CASE(test_arg_parse_size) {
  for (int i = 0; i < 10; i++) {
    int n = rand();
    int m = rand();
    string s = to_string(n) + "x" + to_string(m);
    pair<int, int> res = Parse::get_size(s);
    if (!(res.first == n && res.second == m)) {
      BOOST_FAIL("didn't work with n = " << n << " and m = " << m);
    }
  }
}

pair<vector<string>, vector<pair<int, int>>> gen_grid(int n, int m, int it) {
  vector<string> check;
  vector<pair<int, int>> p;
  for (int i = 0; i < it; i++) {
    int x = rand() % n + 1;
    int y = rand() % m + 1;
    p.push_back({x, y});
    check.push_back(to_string(x) + "x" + to_string(y));
  }
  return {check, p};
}

BOOST_AUTO_TEST_CASE(test_arg_parse_alive) {
  for (int i = 0; i < 10; i++) {
    int n = abs(rand());
    int m = abs(rand());
    int it = rand() % 20 + 1;
    auto g = gen_grid(n, m, it);
    vector<string> check = g.first;
    vector<pair<int, int>> p = g.second;

    vector<pair<int, int>> res = Parse::get_alive(check, n, m);
    for (int i = 0; i < it; i++) {
      if (!(res[i].first == p[i].first && res[i].second == p[i].second)) {
        BOOST_FAIL("didn't work for pair {"
                   << p[i].first << "," << p[i].second << "}"
                   << " ,the actual result is {" << res[i].first << ","
                   << res[i].second << "}");
      }
    }
  }
}

BOOST_AUTO_TEST_CASE(test_read_and_set_field) {
  for (int i = 0; i < 10; i++) {
    int n = abs(rand()) % 100 + 20;
    int m = abs(rand()) % 100 + 20;
    int it = rand() % 20 + 1;
    auto g = gen_grid(n, m, it);
    vector<string> check = g.first;
    vector<pair<int, int>> po = g.second;
    Parse p = Parse();
    vector<pair<int, int>> put = Parse::get_alive(check, n, m);
    Size sz = Size(n, m);
    Field f = Field(sz);
    f.read_and_set(put);
    for (int i = 0; i < it; i++) {
      if (!f.f[po[i].first - 1][po[i].second - 1].getCurState()) {
        BOOST_FAIL("should be true {" << po[i].first - 1 << ","
                                      << po[i].second - 1 << "}, but not");
      }
    }
  }
}
BOOST_AUTO_TEST_CASE(test_count_alive) {
  int n = 20;
  int m = 20;
  vector<string> check = {
    "3x3", "2x2", "2x4", "4x2", "4x4", "5x5", "6x5", "7x5", "1x4"};
  Parse p = Parse();
  vector<pair<int, int>> put = Parse::get_alive(check, n, m);
  Size sz = Size(n, m);
  Field f = Field(sz);
  f.read_and_set(put);
  BOOST_REQUIRE(f.count(2, 2, sz) == 4);
  BOOST_REQUIRE(f.count(4, 3, sz) == 3);
  BOOST_REQUIRE(f.count(7, 7, sz) == 0);
}

void checker(vector<string> check, set<pair<int, int>> res, int n, int m,
  string test_case) {
  Parse p = Parse();
  vector<pair<int, int>> put = Parse::get_alive(check, n, m);
  Size sz = Size(n, m);
  Field f = Field(sz);
  f.read_and_set(put);
  Grid g = Grid(sz, f);
  g.nextGen();
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g.g.f[i][j].getCurState()) {
        if (!res.count({i + 1, j + 1})) {
          BOOST_FAIL("should be  {" << i + 1 << "," << j + 1
                                    << "}, but not in test case " << test_case);
        }
        cnt++;
      }
    }
  }
  if (cnt != res.size()) {
    BOOST_FAIL("should be " << res.size() << ", but get " << cnt
                            << " in test case " << test_case);
  }
}

BOOST_AUTO_TEST_CASE(test_next_gen) {
  int n = 20;
  int m = 20;
  vector<string> check1 = {"2x3", "2x4", "3x2", "3x3", "3x4", "3x5"};
  set<pair<int, int>> res1({{3, 2}, {3, 5}, {4, 3}, {4, 4}, {2, 2}, {2, 5}});
  checker(check1, res1, n, m, "first");
  vector<string> check2 = {
    "2x2", "2x3", "2x4", "3x2", "3x4", "4x2", "4x4", "5x3"};
  set<pair<int, int>> res2({{1, 3}, {2, 2}, {2, 4}, {3, 1}, {3, 2},
    {3, 4}, {3, 5}, {4, 2}, {4, 4}, {5, 3}});
  checker(check2, res2, n, m, "second");
  vector<string> check3 = {"1x1","1x2","1x3","1x4","1x5","2x2","2x3","3x2","3x3","4x3"};
  set<pair<int, int>> res3({{1,1},{1,4},{3,4},{4,2},{4,3}});
  checker(check3, res3, n, m, "third");
}
