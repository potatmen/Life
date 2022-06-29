#include "../include/args_process.h"

pair<string, string> Process::split(string const &s) { // NOLINT
  int pos = s.find('x');
  return {s.substr(0, pos), s.substr(pos + 1, s.length())};
}

pair<int, int> Process::convert(pair<string, string> const &p) { // NOLINT
  return {stoi(p.first), stoi(p.second)};
}