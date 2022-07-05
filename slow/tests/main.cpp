#include <unistd.h>

#include "../include/field.h"
#include "../include/parse.h"

const int t = 1000;

void sleep(int x) {
  unsigned int microsecond = t * x;
  usleep(microsecond);
}

void rec(int depth, int max, bool flag, Field cur, Parse p) {
  cout << "\033[2J\033[1;1H";
  if (depth > max) {
    return;
  }
  cur.print();
  Field next = cur.live();
  if (flag) {
    cout << R"(If you want to play more press "n", else "q".)" << endl;
    string s;
    cin >> s;
    if (s != "n") {
      return;
    }
    rec(depth, max, true, next, p);
  } else {
    sleep(p.opts()["sleep"].as<int>());
    rec(depth + 1, max, false, next, p);
  }
}
const int def_val = 1000;
int main(int ac, char *av[]) {
  int opt;
  po::options_description desc("Allowed options");
  desc.add_options()("help", "produce help message")("batch", po::value<int>(),
    "if set, program runs automatically and you should state the number of "
    "cycles")("sleep", po::value<int>(&opt)->default_value(def_val),
    "the number of miliseconds to wait before new generation "
    "generated, default value is 1000")("size", po::value<string>(),
    "the size of the grid, you can state this value by passing NxM where N "
    "the number of rows, M the number of columns, for example --size 20x30")(
    "put", po::value<vector<string>>(),
    "initial alive cells, you can type many cells by passing NxM where N the "
    "number of row and M the number of column, for example --put 3x7 --put "
    "5x4");
  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

  Parse p = Parse(vm);
  p.build();
  Field clear = Field(p.length(), p.width());
  Field f = clear.rec_add(clear, p.grid(), 0);
  if (vm.count("batch") > 0) {
    rec(0, vm["batch"].as<int>(), false, f, p);
  } else {
    rec(0, 0, true, f, p);
  }
}