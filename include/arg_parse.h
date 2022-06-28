

#ifndef LIFE_PARSE_H
#define LIFE_PARSE_H

#include <bits/stdc++.h>
using namespace std;

class Parse {
public:
  Parse(){};
  static pair<int, int> get_size(string const &s);
  static vector<pair<int, int>> get_alive(vector<string> const &a, int n,
                                          int m);
};

#endif // LIFE_PARSE_H