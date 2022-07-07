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

#ifndef _OOP_PARSE_H_
#define _OOP_PARSE_H_

#include <bits/stdc++.h>

#include <boost/program_options.hpp>
using namespace std;
namespace po = boost::program_options;
class Parse {
private:
  int n = 100000;
  int m = 100000;
  vector<pair<int,int>> points;
  po::variables_map vm;

public:
  Parse() : Parse(nullptr) {}
  Parse(po::variables_map vmp) : vm(vmp) {}  // constructor

  int length() const;
  int width() const;
  vector<pair<int,int>> grid();
  po::variables_map opts();  // getters
  

  vector<pair<int,int>> rec_cells(int pos,vector<pair<int,int>> p);
  static bool has(const string &s, char c);
  static bool valid(string const &s);
  pair<int, int> point(const string &s);
  static pair<int, int> size(const string &s);
  static pair<int, int> split(const string &s);
  void positive();
  void cells();
  void build();  // builders and checkers
};

#endif  //_OOP_PARSE_H_