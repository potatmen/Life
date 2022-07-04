
#ifndef _OOP_PARSE_H_
#define _OOP_PARSE_H_

#include <bits/stdc++.h>

#include <boost/program_options.hpp>
using namespace std;
namespace po = boost::program_options;
class Parse {
private:
  int n;
  int m;
  vector<string> points;
  po::variables_map vm;

public:
  Parse() : Parse(nullptr) {}
  Parse(po::variables_map vmp) : vm(vmp) {}  // constructor

  int length() const;
  int width() const;
  vector<string> grid();
  po::variables_map opts();  // getters

  static bool has(const string &s, char c);
  static bool valid(string const &s);
  static pair<int, int> point(const string &s);
  static pair<int, int> split(const string &s);
  void cells();
  void build();  // builders and checkers
};

#endif  //_OOP_PARSE_H_