#include <iostream>
#include <fstream>

void echo(std::istream &f) {
  f >> std::noskipws;
  char c;
  while (f >> c) std::cout << c;
}

int main(int argc, char *argv[]) {
  if (argc == 1) echo(std::cin);
  else
    for (int i = 1; i < argc; ++i) {
      std::ifstream f {argv[i]};
      echo(f);
    }
}
