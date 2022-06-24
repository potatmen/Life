# John Conway's Game of Life 

<img src="https://play-lh.googleusercontent.com/4xtboOCl4G36He2_RUaYhI9v_eDIoXara2hAxDi99f1R5MwLjSI1QZ_CT6wLdjCTV3E" width="200" height="200" />

![badge](	https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/potatmen/Life/blob/master/LICENSE.txt)
[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

This project aims to show that [John Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) written in C++ using OOP features (inheritance, encapsulation, polymorphism) works slower than the same realization using [EO programming language](https://github.com/objectionary/eo), the more general aim is to show that using EO language is more benifitial for projects that use many objects in terms of exection time.


## Table of Contents

- [Background](#background)
- [Install](#install)
- [Structure](#structure)
- [Usage](#usage)

## Background

According to [previous research](https://github.com/yegor256/fibonacci) measurements showed that C++ realization to count Fibonacci numbers using objects work slowly, therefore, we decided to implement Game of Life. Fibonacci number counting is not sufficient enough because using objects for it's realization is something pulled out of a hat, because we can use a simple loop to count it.
    
## Install

To run it, just do:

```
$ make
$ ./run
```

If you want to clean the environment:
```
$ make clean
```

If you want to formate all .cpp files (clang-format will be called to do so):
```
$ make fix
```

## Structure

![Structure](https://user-images.githubusercontent.com/90863441/175309180-b1e63427-ae4c-48ce-9217-f70ea54096bd.png)


__All ```.cpp``` files include corresponding ```.h``` files that won't be shown.__

The __Main__ object is ```Game( Grid( Size(), Field()) , Repeats())```. 

<br />

__Object ```Repeats()```__ asks for the number of iterations and stores this value, ```cout << "\033[2J\033[1;1H";``` clears the screen after output.

```
Repeats::Repeats() {
  cout << "How many times do you want to iterate?" << endl;
  int x;
  cin >> x;
  rep = x;
  cout << "\033[2J\033[1;1H";
}
```
<br />
<br />

__Object ```Grid()```__ stores the size of the grid and the playing field. In addition to this, it has methods to print the current state and move to the next iteration.

_Constructor._
```
Grid::Grid(Size &st, Field &ff) {
  s = st;
  g = ff;
}
```
<br />

_Method prints grid._ 

```g.f[i][j]``` is the cell in ```i-th``` vertical and ```j-th``` horizontal.

```
void Grid::printGrid() {
  int sz = s.sz;
  for (int i = 0; i < sz * 2 + add; ++i) {
    cout << "-";
  }
  cout << "\n";
  for (int i = 0; i < sz; ++i) {
    cout << "|  ";
    for (int j = 0; j < sz; ++j) {
      if (g.f[i][j].getCurState()) {
        cout << "o ";
      } else {
        cout << ". ";
      }
    }
    cout << " |\n";
  }
  for (int i = 0; i < sz * 2 + add; ++i) {
    cout << "-";
  }
  cout << endl;
}
```
<br />

_Method creating next generation._

ChangeNewState method helps to remember the next generation state of this cell, but we can't change it at the moment, because if we change it, neighbor cells, which are haven't changed yet, will have no information about the current cell in the current generation, what is important for their state in the next generation. After we know all the new states of the cells, we can easily change old values to the new ones.

```
void Grid::nextGen() {

  for (int i = 0; i < s.sz; ++i) {
    for (int j = 0; j < s.sz; ++j) {
      int cnt = g.count(i, j, s.sz);
      if (g.f[i][j].getCurState()) {
        g.f[i][j].changeNewState(cnt == 2 || cnt == 3);
      } else {
        g.f[i][j].changeNewState(cnt == 3);
      }
    }
  }

  for (int i = 0; i < s.sz; ++i) {
    for (int j = 0; j < s.sz; ++j) {
      g.f[i][j].changeCurState();
    }
  }
}

```
<br />
<br />

__Object ```Size()```__ asks for the size of the playing field and stores this value. Flag here is used to make it possible to ask for the size only once. 

```
Size::Size() {
  if (flag) {
    return;
  }
  cout << "Input the size of the square grid: ";
  flag = true;
  int n;
  cin >> n;
  sz = n;
  cout << "\033[2J\033[1;1H";
}
```

<br />
<br />

__Object ```Field()```__ stores the the 2-D array of ```Cell()```. ```Field()``` has methods to ask for initial alive cells and method to count the number of alive neighbor-cells.


_Method setting the initial cells._

```
void Field::read_and_set(Size sz) {

  cout << "Enter the number of coordinates and coordinates of the beginning "
          "cells (numbers from 1 to "
       << sz.sz << ")"
       << "\n";

  int n;
  cin >> n;
  for (int i = 0; i < n; i++) {
    int x;
    int y;
    cin >> x >> y;
    f[x - 1][y - 1].setState(true);
  }
  cout << "\033[2J\033[1;1H";
}
```
<br />

_Method counting alive cells near the cell (x,y)._

At the end we do ```return cnt - static_cast<int>(f[x][y].getCurState())``` beacause we should'n count our cell if it's alive.

```
int Field::count(int x, int y, int sz) {
  int cnt = 0;

  for (int i = x - 1; i <= x + 1; ++i) {
    for (int j = y - 1; j <= y + 1; ++j) {
      if (i < 0 || i > sz - 1 || j < 0 || j > sz - 1) {
        continue;
      }
      cnt += static_cast<int>(f[i][j].getCurState());
    }
  }
  return cnt - static_cast<int>(f[x][y].getCurState());
}

```
<br />
<br />

__Object ```Cell()```__ stores the current state of the cell and state after moving to the new generation. Has methods to change and set values to its attributes.


As mentioned before, newState is a variable that stores the state of the cell in the next generation during its creation. 

```
void Cell::changeNewState(bool val) { newState = val; }

void Cell::changeCurState() { curState = newState; }

void Cell::setState(bool val) { curState = val; }

bool Cell::getCurState() const { return curState; }

```
<br />
<br />

__Object ```Game()```__ performs the game process with the interval of 2 seconds between generations.

```
#include <chrono>
#include <thread>

void sleep() {
  using namespace chrono_literals;
  using chrono::system_clock;
  this_thread::sleep_for(10ns);fun
  this_thread::sleep_until(system_clock::now() + 2s);
}

Game::Game(Grid g, Repeats rep) {
  for (int i = 0; i <= rep.rep; i++) {
    g.printGrid();
    cout << "This is iteratrion number " << i << endl;
    sleep();
    g.nextGen();
    cout << "\033[2J\033[1;1H";
  }
}
```

## Usage
