# John Conway's Game of Life 

<img src="https://play-lh.googleusercontent.com/4xtboOCl4G36He2_RUaYhI9v_eDIoXara2hAxDi99f1R5MwLjSI1QZ_CT6wLdjCTV3E" width="200" height="200" />

![badge](    https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/potatmen/Life/blob/master/LICENSE.txt)

[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

![workflow badge](https://github.com/potatmen/Life/actions/workflows/Life.yml/badge.svg)

This project aims to show that [John Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) written in C++ using OOP features (inheritance, encapsulation, polymorphism) works slower than the same realization using [EO programming language](https://github.com/objectionary/eo), the more general aim is to show that using EO language is more beneficial for projects that use many objects in terms of execution time.

## Table of Contents

- [Background](#background)

- [Install](#install)

- [Usage](#usage)

- [Structure](#structure)

## Background

According to [previous research](https://github.com/yegor256/fibonacci) measurements showed that C++ realization to count Fibonacci numbers using objects work slowly, therefore, we decided to implement Game of Life. Fibonacci number counting is not sufficient enough because using objects for it's realization is something pulled out of a hat, because we can use a simple loop to count it.

    

## Install

At the beginning you need to install boost library, and if you don't have g++, clang-format and clang-tidy. Like this, you can install everything:

```

  sudo apt install g++

  sudo apt-get install libboost-all-dev

  sudo apt-get install -y clang-tidy

  sudo apt install clang-format

```

## Usage

To buld project, just do:

```

$ make

```

Then you can choose which version you prefer more, ```fast_life``` or ```slow_life``` to start the game, if you choose ```fast_life``` just run:

```

$ ./fast_life --help

```

Otherwise:

```

$ ./slow_life --help

```

It will show you all the available options.

All options are the same to both realizations, so ```fast_life``` will be used.

For example, you can enter something like this:

```

$ ./fast_life --batch 20 --size 40x40 --put 3x6 --put 6x8 --put 12x9

```

This will run an automated game with 20 generations on the grid 40X40 with 3 initial alive cells.

If you want to clean the environment:

```

$ make clean

```

If you want to format all .cpp files (clang-format will be called to do so):

```

$ make fix

```

If you want to run tests for ```fast``` or ```slow``` version:

```

$ make fast_test

```

OR

```

$ make slow_test

```

If you want to see a beautiful game called [Gosper glider gun](https://conwaylife.com/wiki/Gosper_glider_gun) run this:

```

 ./fast_life --batch 1000 --sleep 170 --size 40x40 --put 10x26 --put 11x26 --put 11x24  --put 12x14 --put 12x15 --put 12x23 --put 12x22 --put 12x36 --put 12x37 --put 13x13 --put 13x17 --put 13x22 --put 13x23 --put 13x36 --put 13x37 --put 14x2 --put 14x3 --put 14x12 --put 14x18 --put 14x22 --put 14x23  --put 15x2 --put 15x3 --put 15x12 --put 15x16 --put 15x18 --put 15x19 --put 15x24 --put 15x26 --put 16x12 --put 16x18 --put 16x26 --put 17x13 --put 17x17 --put 18x14 --put 18x15

```

If you want to see the infinite loop run:

```

./fast_life --batch 40 --sleep 500 --size 10x10 --put 5x4 --put 5x5 --put 5x6

```

## Structure

## Structure of Slow version

There are some notable features of __Cell__ and __Field__ objects that should be mentioned: all ```for``` statements are replaced with recursion, objects are __immutable__, if we change something, we make a __copy__ of the object and make changes using the constructor, so to change the current object we create new one with changes.

<br />

__Object ```Field()```__ stores the playing field and performs creation of the next generation.

__Details.__ ```rec_line_print``` and ```rec_grid_print``` print the field. ```rec_line_print``` performs creation of the initial field. ```rec_live``` preforms creation of the next generation. ```with``` performs changing of the ```Cell``` in the position ```(x,y)``` by returning a new ```Field``` object with changed cell. ```count``` counts the number of alive cells for the cell with coordinates ```(x,y)```. ```live``` calls ```rec_live``` with special arguments.

```

class Field {

private:

  vector>> grid;

  void rec_line_print(int depth);

  void rec_grid_print(int x, int y);

public:

  Field(int n, int m) : Field(make_grid(n, m)) {}

  Field(vector> g) : grid(g) {}

  vectorCell>> field();  

  Field rec_add(Field cur, vector s, int pos);

  Field rec_live(int x, int y, Field cur);

  static vector<vector<Cell>> make_grid(int n, int m);

  Field live();

  Field with(int x, int y, Cell a);

  void print();  

  int count(int x, int y); 

};

```

<br />

<br />

__Object ```Cell()```__ stores the state (alive/dead) of the cell. Method ```live``` takes an integer to decide whether it will be alive or dead in the next generation and returns ```Cell``` object as a result.

 

```

class Cell {

private:

  bool state;

public:

  Cell(bool st) : state(st) {}

  Cell() : Cell(false) {}  

  bool status() const;  

  Cell live(int cnt) const;  

};

```

<br />

<br />

__Object ```Parse()```__ performs parsing using __BOOST__ library and checks arguments entered in command line.

```

class Parse {

private:

  int n = 100000;

  int m = 100000;

  vector<string> points;

  po::variables_map vm;

public:

  Parse() : Parse(nullptr) {}

  Parse(po::variables_map vmp) : vm(vmp) {} 

  int length() const;

  int width() const;

  vector> grid();

  po::variables_map opts();  

  static bool has(const string &s, char c);

  static bool valid(string const &s);

  pair point(const string &s) const;

  static pair size(const string &s);

  static pair split(const string &s);

  void positive();

  void cells();

  void build();  

};

```

## Structure of Fast version

![Structure](https://user-images.githubusercontent.com/90863441/177322155-579f7f99-be1c-4e54-a9a4-c05e79cf7f11.png)

The __Main__ object is ```Game( Grid( Size(), Field()) , *optional* Repeats())```. 

<br />

__Object ```Repeats()```__ asks for the number of iterations and stores this value.

```

class Repeats {

public:

  int rep;

  Repeats();

};

```

<br />

<br />

__Object ```Grid()```__ stores the size of the grid and the playing field. In addition to this, it has methods to print the current state and move to the next iteration.

```

class Grid {

public:

  Size s;

  Field g;

  Grid(Size &st, Field &ff);

  void printGrid();

  void nextGen();

};

```

<br />

<br />

__Object ```Size()```__ asks for the size of the playing field and stores this value. Flag here is used to make it possible to ask for the size only once. 

```

class Size {

public:

  int n;

  int m;

  Size(){};

  Size(int x, int y);

};

```

<br />

<br />

__Object ```Field()```__ stores the the 2-D array of ```Cell()```. ```Field()``` has methods to ask for initial alive cells and method to count the number of alive neighbor-cells.

```

class Field {

public:

  vector>> f;

  Field(){};

  Field(Size sz);

  void read_and_set(Size sz);

  int count(int x, int y, int sz);

};

```

<br />

<br />

__Object ```Cell()```__ stores the current state of the cell and state after moving to the new generation. Has methods to change and set values to its attributes.

__Details:__ ChangeNewState method helps to remember the next generation state of this cell, but we can't change it at the moment, because if we change it, neighbor cells, which are haven't changed yet, will have no information about the current cell in the current generation, what is important for their state in the next generation. After we know all the new states of the cells, we can easily change old values to the new ones.

As mentioned before, newState is a variable that stores the state of the cell in the next generation during its creation. 

```

class Cell {

private:

  bool curState = false;

  bool newState = false;

public:

  void changeNewState(bool val);

  void changeCurState();

  void setState(bool val);

  bool getCurState() const;

};

```

<br />

<br />

__Object ```Game()```__ performs the game process with the interval of 2 seconds between generations.

```

class Game {

public:

  Game(Grid gr, Repeats rep, int time);

  Game(Grid gr);

};

```

<br />

<br />

__Object ```Parse()```__ performs console arguments parsing and checking.

```

class Parse {

public:

  Parse(){};

  static pair get_size(string const &s);

  static vector> get_alive(vector const &a, int n, int m);

};

```

<br />

<br />

Some objects are not shown because they simply check the correctness of input data and convert strings to ints. 
