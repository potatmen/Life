#ifndef _OOP_CELL_H_
#define _OOP_CELL_H_

using namespace std;
#include <bits/stdc++.h>

class Cell {
private:
  bool state;

public:
  Cell(bool st) : state(st) {}
  Cell() : Cell(false) {}

  // constructors

  bool status() const;  // getter

  Cell live(int cnt) const;  // process
};

#endif  //_OOP_CELL_H_