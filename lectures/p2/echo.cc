#include <iostream>
#include <fstream>
#include "echo.h"

void echo(std::istream &f) {
  f >> std::noskipws;
  char c;
  while (f >> c) std::cout << c;
}
