#include "../include/args_valid.h"
#include "../include/args_check.h"
#include "../include/args_process.h"

bool Valid::is_valid(string const &s) {
  Check c = Check();
  Process p = Process();
  if (Check::has_x(s)) {
    return Check::is_d(p.split(s));
  }
  return false;
}