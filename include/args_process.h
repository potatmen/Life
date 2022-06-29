
#ifndef LIFE_PROCESS_H
#define LIFE_PROCESS_H

#include <bits/stdc++.h>

using namespace std;

class Process {
public:
  Process(){};
  pair<string, string> split(string const &s);
  pair<int, int> convert(pair<string, string> const &p);
};
#endif  // LIFE_PROCESS_H