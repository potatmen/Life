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
const int add = 5;

extern int counter;

vector<vector<Cell>> Field::field() { return grid; }

vector<vector<Cell>> Field::make_grid(int n, int m) {
  //
  counter++;
// 
  vector<vector<Cell>> g;
  g.resize(n);
  for (int i = 0; i < n; i++) {
    g[i].resize(m);
  }
  return g;
}

Field Field::rec_add(Field cur, vector<pair<int, int>> s, int pos) {
  if (pos == s.size()) {
    return cur;
  }
  pair<int, int> x = s[pos];
  
//
  counter++;
// 
  return rec_add(cur.with(x.first - 1, x.second - 1, Cell(true)), s, pos + 1);
}

void Field::rec_line_print(int depth) {
  int m = grid[0].size();
  if (depth == m * 2 + add) {
    cout << "\n";
    return;
  }
  cout << "-";
  rec_line_print(depth + 1);
}

void Field::rec_grid_print(int x, int y) {
  int n = grid.size();
  int m = grid[0].size();
  if (x >= n) {
    return;
  }

  if (y >= m) {
    cout << " |\n";
    rec_grid_print(x + 1, 0);
    return;
  }

  if (y == 0) {
    cout << "|  ";
  }

  if (grid[x][y].status()) {
    cout << "o ";
  } else {
    cout << ". ";
  }
  rec_grid_print(x, y + 1);
}

Field Field::rec_live(int x, int y, Field cur) {
  int n = grid.size();
  int m = grid[0].size();

  if (y == m) {
    return rec_live(x + 1, 0, cur);
  }
  if (x == n) {
    return cur;
  }

//
  counter++;
// 
  Cell replace = cur.field()[x][y].live(count(x, y));

//
  counter++;
// 
  return rec_live(x, y + 1, cur.with(x, y, replace));
}

void Field::print() {
  rec_line_print(0);
  rec_grid_print(0, 0);
  rec_line_print(0);
}

Field Field::live() {
  //
  counter++;
// 
  Field obj = Field(grid);
  return rec_live(0, 0, obj);
}

Field Field::with(int x, int y, Cell a) {
  vector<vector<Cell>> next = grid;
  next[x][y] = a;
  return Field(next);
}

int Field::count(int x, int y) {
  int cnt = 0;
  int n = grid.size();
  int m = grid[0].size();

  // counting the number of alive neighbours
  if (x + 1 < n) {
    cnt += static_cast<int>(grid[x + 1][y].status());
    if (y > 0) {
      cnt += static_cast<int>(grid[x + 1][y - 1].status());
    }
    if (y < m - 1) {
      cnt += static_cast<int>(grid[x + 1][y + 1].status());
    }
  }
  if (x > 0) {
    cnt += static_cast<int>(grid[x - 1][y].status());
    if (y > 0) {
      cnt += static_cast<int>(grid[x - 1][y - 1].status());
    }
    if (y < m - 1) {
      cnt += static_cast<int>(grid[x - 1][y + 1].status());
    }
  }
  if (y > 0) {
    cnt += static_cast<int>(grid[x][y - 1].status());
  }
  if (y < m - 1) {
    cnt += static_cast<int>(grid[x][y + 1].status());
  }
  return cnt;
}