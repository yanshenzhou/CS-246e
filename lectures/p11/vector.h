#ifndef VECTOR_H
#define VECTOR_H
#include <ostream>
#include <cstddef>
namespace CS246E {
class range_error{};

template <typename T> class vector {
  T *theVector;
  size_t n, cap;
  const size_t startSize = 1;
 public:
  vector();
  size_t size() const { return n; }
  const int &operator[](size_t i) const { return theVector[i]; }
  T &operator[](size_t i) { return theVector[i]; }
  void push_back(T n);
  void pop_back();
  ~vector();
  typedef T *iterator;
  typedef const T *const_iterator;

  iterator begin() { return theVector; }
  iterator end() { return theVector + n; }

  const_iterator begin() const { return theVector; }
  const_iterator end() const { return theVector + n; }

  T &at(size_t i);
  const T &at(size_t i) const;

 private:
  void increaseCap();
};

template <typename T> std::ostream &operator<<(std::ostream &out, const vector<T> &v);

template <typename T> vector<T>::vector(): theVector{new T[startSize]}, n{0}, cap{1} {}

template <typename T> void vector<T>::push_back(T x) {
  increaseCap();
  theVector[n++] = x;
}

template <typename T>void vector<T>::pop_back() { if (n > 0) --n; }

template <typename T>vector<T>::~vector() { delete [] theVector; }

template <typename T>T &vector<T>::at(size_t i) {
  if (i < n) return theVector[i];
  throw range_error{};
}

template <typename T>const T &vector<T>::at(size_t i) const {
  if (i < n) return theVector[i];
  throw range_error{};
}

template <typename T>void vector<T>::increaseCap() {
  if (n == cap) {
    T *newVec = new T[2 * cap];
    for (size_t i = 0; i < cap; ++i) newVec[i] = theVector[i];
    delete [] theVector;
    theVector = newVec;
    cap *= 2;
  }
}

template <typename T>std::ostream &operator<<(std::ostream &out, const vector<T> &v) {
  for (auto &n : v) out << n << ' ';
  return out;
}
}
#endif
