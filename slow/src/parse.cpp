#include "../include/parse.h"

#include <utility>

int Parse::length() const { return n; }

int Parse::width() const { return m; }

vector<string> Parse::grid() { return points; }

po::variables_map Parse::opts() { return vm; }

bool Parse::has(const string &s, char c) {
  return s.find(c) < s.length() - 1 && s.find(c) > 0;
}

pair<int, int> Parse::split(const string &s) {
  int pos = s.find('x');
  int left = stoi(s.substr(0, pos));
  int right = stoi(s.substr(pos + 1, s.length()));
  return {left, right};
}

bool Parse::valid(string const &s) {
  pair<int, int> x = split(s);
  return x.first > 0 && x.second > 0;
}

pair<int, int> Parse::point(const string &s) {
  if (has(s, 'x') && valid(s)) {
    return split(s);
  }
  cout << "Incorrect input in size or put";
  exit(0);
}

void Parse::cells() {
  points = vm["put"].as<vector<string>>();
  for (auto &p : points) {
    point(p);
  }
}

void Parse::build() {
  pair<int, int> p = point(vm["size"].as<string>());
  n = p.first;
  m = p.second;
  cells();
}