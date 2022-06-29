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