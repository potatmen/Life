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

#include "../include/field.h"

Field::Field(Size sz) {
  f.resize(sz.n);
  for (int i = 0; i < sz.n; ++i) {
    f[i].resize(sz.m);
  }
}

void Field::read_and_set(vector<pair<int, int>> const &al) {
  for (auto const &i : al) {
    int x;
    int y;
    x = i.first;
    y = i.second;
    f[x - 1][y - 1].setState(true);
  }
  //  cout << "\033[2J\033[1;1H";
}

int Field::count(int x, int y, Size sz) {
  int cnt = 0;

  for (int i = x - 1; i <= x + 1; ++i) {
    for (int j = y - 1; j <= y + 1; ++j) {
      if (i < 0 || i > sz.n - 1 || j < 0 || j > sz.m - 1) {
        continue;
      }
      cnt += static_cast<int>(f[i][j].getCurState());
    }
  }
  return cnt - static_cast<int>(f[x][y].getCurState());
}