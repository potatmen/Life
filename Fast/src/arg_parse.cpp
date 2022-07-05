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

#include "../include/arg_parse.h"

#include <string>
#include <vector>

#include "../include/args_process.h"
#include "../include/args_valid.h"
const int size = 20;
pair<int, int> Parse::get_size(string const &s) {
  if (s.length() == 0) {
    return {size, size};
  }

  Valid v = Valid();

  if (Valid::is_valid(s)) {
    Process p = Process();
    return p.convert(p.split(s));
  }
  cout << "Incorrect arguments in size option" << endl;
  exit(0);
}

vector<pair<int, int>> Parse::get_alive(vector<string> const &a, int n, int m) {
  vector<pair<int, int>> res;
  for (auto const &i : a) {
    Valid v = Valid();
    if (Valid::is_valid(i)) {
      Process p = Process();
      pair<int, int> x = p.convert(p.split(i));
      if (x.first <= 0 || x.first > n || x.second <= 0 || x.second > m) {
        cout << "You entered cells out of range of the grid " << i << endl;
        exit(0);
      }
      res.emplace_back(x);
    } else {
      cout << "You entered incorrect arguments in put option" << endl;
      exit(0);
    }
  }
  return res;
}