#include "../include/arg_parse.h"
#include <string>
#include <vector>
const int size = 20;
pair<int, int> Parse::get_size(std::string const &s) {
  if (s.length() == 0) {
    return {size, size};
  }
  int ind = s.find('x');
  return make_pair(stoi(s.substr(0, ind)), stoi(s.substr(ind + 1, s.length())));
}

vector<pair<int, int>> Parse::get_alive(vector<string> const &a) {
  vector<pair<int, int>> res;
  for (auto const &i : a) {
    int ind = i.find('x');
    res.emplace_back(
        make_pair(stoi(i.substr(0, ind)), stoi(i.substr(ind + 1, i.length()))));
  }
  return res;
}