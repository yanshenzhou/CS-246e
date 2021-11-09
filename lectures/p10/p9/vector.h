#ifndef VECTOR_H
#define VECTOR_H
#include <ostream>
#include <cstddef>
namespace CS246E {
class range_error{};

class vector {
  int *theVector;
  size_t n, cap;
 public:
  vector();
  size_t size() const { return n; }
  const int &operator[](size_t i) const { return theVector[i]; }
  int &operator[](size_t i) { return theVector[i]; }
  void push_back(int n);
  void pop_back();
  ~vector();
  typedef int *iterator;
  typedef const int *const_iterator;

  iterator begin() { return theVector; }
  iterator end() { return theVector + n; }

  const_iterator begin() const { return theVector; }
  const_iterator end() const { return theVector + n; }

  int &at(size_t i);
  const int &at(size_t i) const;

 private:
  void increaseCap();
};

std::ostream &operator<<(std::ostream &out, const vector &v);
}
#endif
