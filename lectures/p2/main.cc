#include <iostream>
#include <fstream>
#include "echo.h"

int main(int argc, char *argv[]) {
  if (argc == 1) echo(std::cin);
  else
    for (int i = 1; i < argc; ++i) {
      std::ifstream f {argv[i]};
      echo(f);
    }
}
