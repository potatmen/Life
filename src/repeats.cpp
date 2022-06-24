#include "../include/repeats.h"

Repeats::Repeats() {
  cout << "How many times do you want to iterate?" << endl;
  int x;
  cin >> x;
  rep = x;
  cout << "\033[2J\033[1;1H";
}