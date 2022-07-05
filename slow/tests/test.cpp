#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

#include "../include/cell.h"
#include "../include/field.h"
#include "../include/parse.h"
BOOST_AUTO_TEST_CASE(test_cell_live) {
  Cell a = Cell(true);
  Cell b = Cell(false);
  BOOST_REQUIRE(!a.live(4).status());
  BOOST_REQUIRE(a.live(2).status());
  BOOST_REQUIRE(a.live(3).status());
  BOOST_REQUIRE(!a.live(0).status());
  BOOST_REQUIRE(b.live(3).status());
  BOOST_REQUIRE(!b.live(1).status());
  BOOST_REQUIRE(!b.live(2).status());
}

BOOST_AUTO_TEST_CASE(test_field_build) {
  int n = 15;
  int m = 10;
  vector<string> s = {"2x7", "3x7", "6x8", "1x1", "3x3", "10x10", "14x1"};
  set<pair<int, int>> p = {
    {2, 7}, {3, 7}, {6, 8}, {1, 1}, {3, 3}, {10, 10}, {14, 1}};
  Field f = Field(n, m);
  auto g = f.rec_add(f, s, 0).field();
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j].status()) {
        cnt++;
        if (!p.count({i + 1, j + 1})) {
          BOOST_FAIL(
            " in grid should be  {" << i + 1 << "," << j + 1 << "}, but not");
        }
      }
    }
  }
  BOOST_REQUIRE(cnt == p.size());
}

BOOST_AUTO_TEST_CASE(test_field_count) {
  int n = 20;
  int m = 20;
  vector<string> check = {
    "3x3", "2x2", "2x4", "4x2", "4x4", "5x5", "6x5", "7x5", "1x4"};
  Field f = Field(n, m);
  f = f.rec_add(f, check, 0);
  BOOST_REQUIRE(f.count(2, 2) == 4);
  BOOST_REQUIRE(f.count(4, 3) == 3);
  BOOST_REQUIRE(f.count(7, 7) == 0);
}

BOOST_AUTO_TEST_CASE(test_field_with) {
  int n = 20;
  int m = 20;
  vector<string> check = {
    "3x3", "2x2", "2x4", "4x2", "4x4", "5x5", "6x5", "7x5", "1x4"};
  Field f = Field(n, m);
  f = f.rec_add(f, check, 0);
  Cell add = Cell(true);
  f = f.with(1, 2, add);
  f = f.with(3, 2, add);
  add = Cell(false);
  f = f.with(2, 2, add);
  f = f.with(0, 3, add);
  auto g = f.field();
  BOOST_REQUIRE(g[1][2].status());
  BOOST_REQUIRE(g[3][2].status());
  BOOST_REQUIRE(!g[2][2].status());
  BOOST_REQUIRE(!g[0][3].status());
}

void checker(vector<string> check, set<pair<int, int>> res, int n, int m,
  string test_case) {
  Field f = Field(n, m);
  f = f.rec_add(f, check, 0);
  auto g = f.live().field();
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j].status()) {
        cnt++;
        if (!res.count({i + 1, j + 1})) {
          BOOST_FAIL(" in grid should be  {" << i + 1 << "," << j + 1
                                             << "}, but not in case "
                                             << test_case);
        }
      }
    }
  }
  if (cnt != res.size()) {
    BOOST_FAIL("should be " << res.size() << " number of points, but get "
                            << cnt << " in test case " << test_case);
  }
}

BOOST_AUTO_TEST_CASE(test_field_live) {
  int n = 20;
  int m = 20;
  vector<string> check1 = {"2x3", "2x4", "3x2", "3x3", "3x4", "3x5"};
  set<pair<int, int>> res1({{3, 2}, {3, 5}, {4, 3}, {4, 4}, {2, 2}, {2, 5}});
  checker(check1, res1, n, m, "first");
  vector<string> check2 = {
    "2x2", "2x3", "2x4", "3x2", "3x4", "4x2", "4x4", "5x3"};
  set<pair<int, int>> res2({{1, 3}, {2, 2}, {2, 4}, {3, 1}, {3, 2}, {3, 4},
    {3, 5}, {4, 2}, {4, 4}, {5, 3}});
  checker(check2, res2, n, m, "second");
  vector<string> check3 = {
    "1x1", "1x2", "1x3", "1x4", "1x5", "2x2", "2x3", "3x2", "3x3", "4x3"};
  set<pair<int, int>> res3({{1, 1}, {1, 4}, {3, 4}, {4, 2}, {4, 3}});
  checker(check3, res3, n, m, "third");
}

BOOST_AUTO_TEST_CASE(test_points_get){
  Parse p = Parse();
  auto res = p.point("11x3");
  BOOST_REQUIRE(res.first == 11 && res.second == 3);
  res = p.point("5x100");
  BOOST_REQUIRE(res.first == 5 && res.second == 100);
  res = p.point("3x1");
  BOOST_REQUIRE(res.first == 3 && res.second == 1);
}