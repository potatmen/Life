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
const int cycles = 25;

int main(int ac, char *av[]) { // NOLINT

  int opt;
  po::options_description desc("Allowed options");
  desc.add_options()("help", "produce help message")(
      "batch", "if set, program runs automatically")(
      "cycles", po::value<int>(&opt)->default_value(cycles),
      "the number of cycles")("size", po::value<string>(),
                              "the size of the grid")(
      "put", po::value<vector<string>>(),
      "initial alive cells, you can type many cells");

  po::variables_map vm;
  po::store(po::parse_command_line(ac, av, desc), vm);
  po::notify(vm);

  if (vm.count("help") > 0) {
    cout << desc << "\n";
    return 0;
  }
  cout << "\033[2J\033[1;1H";

  Parse p = Parse();
  pair<int, int> size = Parse::get_size(vm["size"].as<string>());
  vector<pair<int, int>> put = Parse::get_alive(vm["put"].as<vector<string>>());

  Size sz = Size(size.first, size.second);
  Field f = Field(sz);
  f.read_and_set(put);

  if (vm.count("batch") > 0) {
    Game g = Game(Grid(sz, f), Repeats(vm["cycles"].as<int>()));
  } else {
    Game g = Game(Grid(sz, f));
  }
}
