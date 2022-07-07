
// Copyright (c) 2022 Anton Shatokhin

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <boost/test/unit_test.hpp>
#include <utility>

#include "../../include/field.h"

void checker(vector<pair<int,int>> check, const set<pair<int, int>>& res, int n, int m,
  const string& test_case) {
  Field f = Field(n, m);
  f = f.rec_add(f, std::move(check), 0);
  auto g = f.live().field();
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j].status()) {
        cnt++;
        if (res.count({i + 1, j + 1}) == 0u) {
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
  vector<pair<int,int>> check1 = {{2,3}, {2,4}, {3,2}, {3,3}, {3,4}, {3,5}};
  set<pair<int, int>> res1({{3, 2}, {3, 5}, {4, 3}, {4, 4}, {2, 2}, {2, 5}});
  checker(check1, res1, n, m, "first");
  vector<pair<int,int>> check2 = {
    {2,2}, {2,3}, {2,4}, {3,2}, {3,4}, {4,2}, {4,4}, {5,3}};
  set<pair<int, int>> res2({{1, 3}, {2, 2}, {2, 4}, {3, 1}, {3, 2}, {3, 4},
    {3, 5}, {4, 2}, {4, 4}, {5, 3}});
  checker(check2, res2, n, m, "second");
  vector<pair<int,int>> check3 = {
    {1,1}, {1,2}, {1,3}, {1,4}, {1,5}, {2,2}, {2,3}, {3,2}, {3,3}, {4,3}};
  set<pair<int, int>> res3({{1, 1}, {1, 4}, {3, 4}, {4, 2}, {4, 3}});
  checker(check3, res3, n, m, "third");
}