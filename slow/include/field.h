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

#ifndef _OOP_FIELD_H_
#define _OOP_FIELD_H_

#include <bits/stdc++.h>

#include "cell.h"

using namespace std;

class Field {
private:
  vector<vector<Cell>> grid;
  void rec_line_print(int depth);
  void rec_grid_print(int x, int y);

public:
  Field(int n, int m) : Field(make_grid(n, m)) {}
  Field(vector<vector<Cell>> g) : grid(g) {}

  vector<vector<Cell>> field();  // getters

  Field rec_add(Field cur, vector<pair<int, int>> s, int pos);
  Field rec_live(int x, int y, Field cur);

  static vector<vector<Cell>> make_grid(int n, int m);
  Field live();
  Field with(int x, int y, Cell a);
  void print();  // next_gen makers
  int count(int x, int y);
};

#endif  //_OOP_FIELD_H_