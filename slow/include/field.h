
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

  Field rec_add(Field cur, vector<string> s, int pos);
  Field rec_live(int x, int y, Field cur);

  static vector<vector<Cell>> make_grid(int n, int m);
  Field live();
  Field with(int x, int y, Cell a);
  void print();  // next_gen makers
  int count(int x, int y);
};

#endif  //_OOP_FIELD_H_