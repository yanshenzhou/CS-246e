#include <iostream>
#include "vector.h"

using cs246e::vector;

int main() {
  vector v;

  for (cs246e::vector::const_iterator i = v.begin(); i != v.end(); ++i) {
     std::cout << *i << std::endl;
  }
  for (cs246e::vector::iterator i = v.begin(); i != v.end(); ++i) {
     std::cout << *i << std::endl;
  }

  std::cout << "rev" << std::endl;

  for (cs246e::vector::reverse_iterator i = v.rbegin(); i != v.rend(); ++i) {
     std::cout << *i << std::endl;
  }
  const vector r = v;
  for (cs246e::vector::const_reverse_iterator i = r.rbegin(); i != r.rend(); ++i) {
     std::cout << *i << std::endl;
  }
}
