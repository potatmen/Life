
#include "../include/game.h"

#include <unistd.h>
const int mult = 1000;
void sleep(int time) {
  unsigned int microsecond = time * mult;
  usleep(microsecond);
}

Game::Game(Grid g, Repeats rep, int time) {
  for (int i = 0; i <= rep.rep; i++) {
    cout << "\033[2J\033[1;1H";
    g.printGrid();
    cout << "This is iteratrion number " << i << endl;
    sleep(time);
    g.nextGen();
  }
}

Game::Game(Grid g) {
  while (true) {
    cout << "\033[2J\033[1;1H";
    g.printGrid();
    cout << R"(If you want to carry on, type "n", else type "q")" << endl;
    string s;
    cin >> s;
    if (s == "n") {
      g.nextGen();
    } else {
      return;
    }
  }
}