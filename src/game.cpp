
#include "../include/game.h"

#include <chrono>
#include <thread>

void sleep() {
  using namespace chrono_literals;
  using chrono::system_clock;
  this_thread::sleep_for(10ns);
  this_thread::sleep_until(system_clock::now() + 2s);
}

Game::Game(Grid g, Repeats rep) {
  for (int i = 0; i <= rep.rep; i++) {
    g.printGrid();
    cout << "This is iteratrion number " << i << endl;
    ;
    sleep();
    g.nextGen();
    cout << "\033[2J\033[1;1H";
  }
}
