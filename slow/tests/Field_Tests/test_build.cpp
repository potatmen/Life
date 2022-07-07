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

#include "../../include/field.h"

BOOST_AUTO_TEST_CASE(test_field_build) {
  int n = 15;
  int m = 10;
  set<pair<int, int>> p = {
    {2, 7}, {3, 7}, {6, 8}, {1, 1}, {3, 3}, {10, 10}, {14, 1}};
  vector<pair<int,int>> r= {{2, 7}, {3, 7}, {6, 8}, {1, 1}, {3, 3}, {10, 10}, {14, 1}};
  Field f = Field(n, m);
  auto g = f.rec_add(f, r, 0).field();
  int cnt = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (g[i][j].status()) {
        cnt++;
        if (p.count({i + 1, j + 1}) == 0) {
          BOOST_FAIL(
            " in grid should be  {" << i + 1 << "," << j + 1 << "}, but not");
        }
      }
    }
  }
  BOOST_REQUIRE(cnt == p.size());
}