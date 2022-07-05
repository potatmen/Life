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

#include "../include/grid.h"

const int add = 5;

Grid::Grid(Size &st, Field &ff) {
  s = st;
  g = ff;
}

void Grid::printGrid() {
  for (int i = 0; i < s.m * 2 + add; ++i) {
    cout << "-";
  }
  cout << "\n";
  for (int i = 0; i < s.n; ++i) {
    cout << "|  ";
    for (int j = 0; j < s.m; ++j) {
      if (g.f[i][j].getCurState()) {
        cout << "o ";
      } else {
        cout << ". ";
      }
    }
    cout << " |\n";
  }
  for (int i = 0; i < s.m * 2 + add; ++i) {
    cout << "-";
  }
  cout << endl;
}

void Grid::nextGen() {
  for (int i = 0; i < s.n; ++i) {
    for (int j = 0; j < s.m; ++j) {
      int cnt = g.count(i, j, s);
      if (g.f[i][j].getCurState()) {
        g.f[i][j].changeNewState(cnt == 2 || cnt == 3);
      } else {
        g.f[i][j].changeNewState(cnt == 3);
      }
    }
  }

  for (int i = 0; i < s.n; ++i) {
    for (int j = 0; j < s.m; ++j) {
      g.f[i][j].changeCurState();
    }
  }
}
