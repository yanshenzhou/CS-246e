#include <cstddef>
#include "vector.h"
namespace {
void increaseCap(CS246E::vector &v) {
  if (v.size == v.cap) {
    int *newVec = new int[2 * v.cap];
    for (size_t i = 0; i < v.cap; ++i) newVec[i] = v.theVector[i];
    delete [] v.theVector;
    v.theVector = newVec;
    v.cap *= 2;
  }
}
}

CS246E::vector CS246E::make_vector() {
  vector v {new int [startSize], 0, 1};
  return v;
}

size_t CS246E::size(const vector &v) { return v.size; }

int &CS246E::itemAt(const vector &v, size_t i) { return v.theVector[i]; }

void CS246E::push_back(vector &v, int n) {
  increaseCap(v);
  v.theVector[v.size++] = n;
}

void CS246E::pop_back(vector &v) { if (v.size > 0) --v.size; }

void CS246E::dispose(vector &v) { delete [] v.theVector; }
