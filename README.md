# John Conway's Game of Life 

<img src="https://play-lh.googleusercontent.com/4xtboOCl4G36He2_RUaYhI9v_eDIoXara2hAxDi99f1R5MwLjSI1QZ_CT6wLdjCTV3E" width="200" height="200" />

![badge](	https://img.shields.io/badge/C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B&logoColor=white)

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://github.com/potatmen/Life/blob/master/LICENSE.txt)
[![standard-readme compliant](https://img.shields.io/badge/readme%20style-standard-brightgreen.svg?style=flat-square)](https://github.com/RichardLitt/standard-readme)

This project aims to show that [John Conway's Game of Life](https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life) written in C++ using OOP features (inheritance, encapsulation, polymorphism) works slower than the same realization using [EO programming language](https://github.com/objectionary/eo), the more general aim is to show that using EO language is more benifitial for projects that use many objects in terms of exection time.


## Table of Contents

- [Background](#background)
- [Install](#install)
- [Realization](#structure)
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

The main object is ```Game( Grid( Size(), Field()) , Repeats())```. 

Object ```Repeats()``` asks for the number of iterations and stores this value. 

Object ```Grid()``` stores the size of the grid and the playing field. In addition to this, it has methods to print the current state and move to the next iteration. 

Object ```Size()``` asks for the size of the playing field and stores this value.

Object ```Field()``` stores the the 2-D array of ```Cell()```. ```Field()``` has methods to ask for initial alive cells and method to count the number of alive neighbour-cells.

Object ```Cell()``` stores the current state of the cell and state after moving to the new generation. Has methods to change and set values to it's attributes.

Object ```Game()``` performs the game process.

## Usage
