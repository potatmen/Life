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
