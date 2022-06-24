#include "../include/field.h"

Field::Field(Size sz) {
  f.resize(sz.sz);
  for (int i = 0; i < sz.sz; ++i) {
    f[i].resize(sz.sz);
  }
}

void Field::read_and_set(Size sz) {

  cout << "Enter the number of coordinates and coordinates of the beginning "
          "cells (numbers from 1 to "
       << sz.sz << ")"
       << "\n";

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    int y;
    cin >> x >> y;
    f[x - 1][y - 1].setState(true);
  }
  cout << "\033[2J\033[1;1H";
}

int Field::count(int x, int y, int sz) {
  int cnt = 0;

  for (int i = x - 1; i <= x + 1; ++i) {
    for (int j = y - 1; j <= y + 1; ++j) {
      if (i < 0 || i > sz - 1 || j < 0 || j > sz - 1) {
        continue;
      }
      cnt += static_cast<int>(f[i][j].getCurState());
    }
  }
  return cnt - static_cast<int>(f[x][y].getCurState());
}