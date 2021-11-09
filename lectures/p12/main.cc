#include <iostream>
#include "vector.h"

using CS246E::vector;

int main() {
  vector<int> v;
  v.push_back(1);
  v.push_back(10);
  v.push_back(100);
  v.at(0) = 2;

  vector<int> w(10);

  std::cout << v << std::endl;
  std::cout << w << std::endl;

  vector<int> x(10, 5);
  std::cout << x << std::endl;

  vector<int> y {2,3,5,7,11};
  std::cout << y << std::endl;
}
