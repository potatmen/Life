#include "../include/field.h"
#include "../include/game.h"
#include "../include/grid.h"
#include "../include/repeats.h"
#include "../include/size.h"
int main() {
  Size sz = Size();
  Field f = Field(sz);
  f.read_and_set(sz);
  Game g = Game(Grid(sz, f), Repeats());
}