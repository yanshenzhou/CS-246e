#ifndef VECTOR_H
#define VECTOR_H
#include <cstddef>
namespace CS246E {
struct vector {
  size_t n, cap;
  int *theVector;
  vector();
  vector(const vector&);
  vector(vector&&);
  size_t size();
  int &itemAt(size_t i);
  void push_back(int n);
  void pop_back();
  ~vector();
};
}
#endif
