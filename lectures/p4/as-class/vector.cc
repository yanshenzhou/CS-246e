#include <cstddef>
#include <iostream>
#include "vector.h"
namespace {
void increaseCap(CS246E::vector &v) {
  if (v.n == v.cap) {
    int *newVec = new int[2 * v.cap];
    for (size_t i = 0; i < v.cap; ++i) newVec[i] = v.theVector[i];
    delete [] v.theVector;
    v.theVector = newVec;
    v.cap *= 2;
  }
}

const int startSize = 1;
}

CS246E::vector::vector(): n{0}, cap{startSize}, theVector {new int [startSize]} {
  std::cout << "Basic ctor" << std::endl;
}

CS246E::vector::vector(const vector &other): n{other.n}, cap{other.cap},
theVector{other.theVector} {  // Note: this is incorect (shallow)
  std::cout << "Copy ctor" << std::endl;
}

CS246E::vector::vector(vector &&other): n{other.n}, cap{other.cap},
theVector{other.theVector} {  // Note: this is incorect (shallow)
  std::cout << "Move ctor" << std::endl;
}

size_t CS246E::vector::size() { return n; }

int &CS246E::vector::itemAt(size_t i) { return theVector[i]; }

void CS246E::vector::push_back(int x) {
  increaseCap(*this);
  theVector[n++] = x;
}

void CS246E::vector::pop_back() { if (n > 0) --n; }

CS246E::vector::~vector() { delete [] theVector; }
