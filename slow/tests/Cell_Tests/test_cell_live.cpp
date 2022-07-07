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

#define BOOST_TEST_MODULE MyTest
#include <boost/test/included/unit_test.hpp>

int counter = 0;
#include "../../include/cell.h"

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
