#include "../include/grid.h"

const int add = 5;

Grid::Grid(Size &st, Field &ff) {
  s = st;
  g = ff;
}

void Grid::printGrid() {
  int sz = s.sz;
  for (int i = 0; i < sz * 2 + add; ++i) {
    cout << "-";
  }
  cout << "\n";
  for (int i = 0; i < sz; ++i) {
    cout << "|  ";
    for (int j = 0; j < sz; ++j) {
      if (g.f[i][j].getCurState()) {
        cout << "o ";
      } else {
        cout << ". ";
      }
    }
    cout << " |\n";
  }
  for (int i = 0; i < sz * 2 + add; ++i) {
    cout << "-";
  }
  cout << endl;
}

void Grid::nextGen() {

  for (int i = 0; i < s.sz; ++i) {
    for (int j = 0; j < s.sz; ++j) {
      int cnt = g.count(i, j, s.sz);
      if (g.f[i][j].getCurState()) {
        g.f[i][j].changeNewState(cnt == 2 || cnt == 3);
      } else {
        g.f[i][j].changeNewState(cnt == 3);
      }
    }
  }

  for (int i = 0; i < s.sz; ++i) {
    for (int j = 0; j < s.sz; ++j) {
      g.f[i][j].changeCurState();
    }
  }
}
