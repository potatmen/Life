#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

#include "../include/arg_parse.h"
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

BOOST_AUTO_TEST_CASE(test_arg_parse_alive) {
  for (int i = 0; i < 10; i++) {
    int n = abs(rand());
    int m = abs(rand());
    int it = rand() % 20 + 1;
    vector<string> check;
    vector<pair<int, int>> p;
    for (int i = 0; i < it; i++) {
      int x = rand() % n + 1;
      int y = rand() % m + 1;
      p.push_back({x, y});
      check.push_back(to_string(x) + "x" + to_string(y));
    }
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
