
#ifndef LIFE_GAME_H
#define LIFE_GAME_H

#include "grid.h"
#include "repeats.h"
class Game {
public:
  Game(Grid gr, Repeats rep);
  Game(Grid gr);
};

#endif // LIFE_GAME_H
