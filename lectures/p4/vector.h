#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
namespace CS246E {
struct vector {
  int *theVector;
  size_t size, cap;
};

const size_t startSize = 1;

vector make_vector();

size_t size(const vector &v);

int &itemAt(const vector &v, size_t i);

void push_back(vector &v, int n);

void pop_back(vector &v);

void dispose(vector &v);
}
#endif
