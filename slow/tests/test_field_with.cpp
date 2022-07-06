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

#include "../include/cell.h"
#include "../include/field.h"

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