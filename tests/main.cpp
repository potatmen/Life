#include "../include/arg_parse.h"
#include "../include/field.h"
#include "../include/game.h"
#include "../include/grid.h"
#include "../include/repeats.h"
#include "../include/size.h"
#include <boost/program_options.hpp>
#include <iostream>
#include <string>
#include <vector>

namespace po = boost::program_options;
const int def_val = 1000;
int main(int ac, char *av[]) { // NOLINT

  int opt;
  po::options_description desc("Allowed options");
  desc.add_options()("help", "produce help message")(
      "batch", po::value<int>(),
      "if set, program runs automatically and you should state the number of "
      "cycles")("sleep", po::value<int>(&opt)->default_value(def_val),
                "the number of miliseconds to wait before new generation "
                "generated, default value is 1000")(
      "size", po::value<string>(),
      "the size of the grid, you can state this value by passing NxM where N "
      "the number of rows, M the number of columns, for example --size 20x30")(
      "put", po::value<vector<string>>(),
      "initial alive cells, you can type many cells by passing NxM where N the "
      "number of row and M the number of column, for example --put 3x7 --put "
      "5x4");

  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

  if (vm.count("help") > 0) {
    cout << desc << "\n";
    return 0;
  }

  Parse p = Parse();
  pair<int, int> size = Parse::get_size(vm["size"].as<string>());
  vector<pair<int, int>> put =
      Parse::get_alive(vm["put"].as<vector<string>>(), size.first, size.second);

  Size sz = Size(size.first, size.second);
  Field f = Field(sz);
  f.read_and_set(put);

  if (vm.count("batch") > 0) {
    Game g = Game(Grid(sz, f), Repeats(vm["batch"].as<int>()),
                  vm["sleep"].as<int>());
  } else {
    Game g = Game(Grid(sz, f));
  }
}
