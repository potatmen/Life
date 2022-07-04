#include "../include/args_check.h"

bool Check::has_x(string const &s) {
  return s.find('x') < s.length() - 1 && s.find('x') > 0;
}

bool Check::is_d(pair<string, string> const &p) {
  for (char const &c : p.first) {
    if (isdigit(c) == 0) {
      return false;
    }
  }
  for (char const &c : p.second) {
    if (isdigit(c) == 0) {
      return false;
    }
  }
  return stoi(p.first) > 0 && stoi(p.second) > 0;
}
