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

#include "../../include/arg_parse.h"
#include "../../include/field.h"
#include "../../include/grid.h"
#include "../../include/size.h"

pair<vector<string>, vector<pair<int, int>>> get_grid(int n, int m, int it) {
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

BOOST_AUTO_TEST_CASE(test_read_and_set_field) {
  for (int i = 0; i < 10; i++) {
    int n = abs(rand()) % 100 + 20;
    int m = abs(rand()) % 100 + 20;
    int it = rand() % 20 + 1;
    auto g = get_grid(n, m, it);
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