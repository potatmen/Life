#include "../include/size.h"
bool flag = false;
Size::Size() {
  if (flag) {
    return;
  }
  cout << "Input the size of the square grid: ";
  flag = true;
  int n;
  cin >> n;
  sz = n;
  cout << "\033[2J\033[1;1H";
}