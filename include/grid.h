
#ifndef LIFE_GRID_H
#define LIFE_GRID_H

#include "field.h"
#include "size.h"

class Grid {
public:
  Size s;
  Field g;
  Grid(Size &st, Field &ff);
  void printGrid();
  void nextGen();
};

#endif // LIFE_GRID_H
