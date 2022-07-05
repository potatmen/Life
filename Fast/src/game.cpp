// Copyright (c) 2022 Anton Shatokhin

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included
// in all copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

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