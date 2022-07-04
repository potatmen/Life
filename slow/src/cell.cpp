#include "../include/cell.h"

bool Cell::status() const { return state; }

Cell Cell::live(int cnt) const {
  return {state && (cnt == 2 || cnt == 3) || !state && (cnt == 3)};
}