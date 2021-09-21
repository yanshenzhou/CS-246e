#include "vector.h"

using CS246E::vector;

int main() {
  vector v = CS246E::make_vector();
  push_back(v, 1);
  push_back(v, 10);
  push_back(v, 100);

  dispose(v);
}
