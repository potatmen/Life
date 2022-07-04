
#include "../include/field.h"

#include "../include/parse.h"
const int add = 5;

vector<vector<Cell>> Field::field() { return grid; }

vector<vector<Cell>> Field::make_grid(int n, int m) {
  vector<vector<Cell>> g;
  g.resize(n);
  for (int i = 0; i < n; i++) {
    g[i].resize(m);
  }
  return g;
}

Field Field::rec_add(Field cur, vector<string> s, int pos) {
  if (pos == s.size()) {
    return cur;
  }
  Parse p = Parse();
  pair<int, int> x = Parse::point(s[pos]);
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
  Cell replace = cur.field()[x][y].live(count(x, y));

  return rec_live(x, y + 1, cur.with(x, y, replace));
}

void Field::print() {
  rec_line_print(0);
  rec_grid_print(0, 0);
  rec_line_print(0);
}

Field Field::live() {
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