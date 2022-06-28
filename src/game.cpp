
#include "../include/game.h"

#include <chrono>
#include <thread>

void sleep() {
  using namespace chrono_literals;
  using chrono::system_clock;
  this_thread::sleep_for(10ns);
  this_thread::sleep_until(system_clock::now() + 1s);
}

Game::Game(Grid g, Repeats rep) {
  for (int i = 0; i <= rep.rep; i++) {
    cout << "\033[2J\033[1;1H";
    g.printGrid();
    cout << "This is iteratrion number " << i << endl;
    sleep();
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