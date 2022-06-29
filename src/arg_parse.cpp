#include "../include/arg_parse.h"

#include <string>
#include <vector>

#include "../include/args_process.h"
#include "../include/args_valid.h"
const int size = 20;
pair<int, int> Parse::get_size(string const &s) {
  if (s.length() == 0) {
    return {size, size};
  }

  Valid v = Valid();

  if (Valid::is_valid(s)) {
    Process p = Process();
    return p.convert(p.split(s));
  }
  cout << "Incorrect arguments in size option" << endl;
  exit(0);
}

vector<pair<int, int>> Parse::get_alive(vector<string> const &a, int n, int m) {
  vector<pair<int, int>> res;
  for (auto const &i : a) {
    Valid v = Valid();
    if (Valid::is_valid(i)) {
      Process p = Process();
      pair<int, int> x = p.convert(p.split(i));
      if (x.first <= 0 || x.first > n || x.second <= 0 || x.second > m) {
        cout << "You entered cells out of range of the grid " << i << endl;
        exit(0);
      }
      res.emplace_back(x);
    } else {
      cout << "You entered incorrect arguments in put option" << endl;
      exit(0);
    }
  }
  return res;
}