#include <iostream>
#include "vector.h"

using CS246E::vector;

int main() {
  vector v;
  v.push_back(1);
  v.push_back(10);
  v.push_back(100);
  v.at(0) = 2;

  std::cout << v << std::endl;

  v.at(3);
}
