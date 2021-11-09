#ifndef VECTOR_H
#define VECTOR_H
#include <ostream>
#include <iostream>
#include <cstddef>
#include <initializer_list>
#include "fillcopy.h"
namespace CS246E {
class range_error{};

template <typename T> class vector {
  static const size_t startSize = 1;
  size_t n, cap;
  T *theVector;
 public:
  vector();
  vector(size_t n, T i = T{});
  vector(const vector &other);
  vector(std::initializer_list<T> init);
  size_t size() const { return n; }
  bool empty() const { return !n; }
  const int &operator[](size_t i) const { return theVector[i]; }
  T &operator[](size_t i) { return theVector[i]; }
  void push_back(const T &x);
  void push_back(T &&x);
  void pop_back();
  ~vector();
  template <typename... Args> void emplace_back(Args&&... args);
  using iterator = T*;
  using const_iterator = const T*;

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

template <typename T> vector<T>::vector(): n{0}, cap{startSize}, theVector{static_cast<T*>(operator new(sizeof(T)))} {}

template <typename T> vector<T>::vector(size_t n, T i): n{n}, cap{n?n:startSize}, theVector{static_cast<T*>(operator new(cap * sizeof(T)))} {
  try {
    uninitialized_fill(theVector, theVector + n, i);
  }
  catch(...) {
    operator delete(theVector);
    throw;
  }
}

template<typename T> vector<T>::vector(const vector &other): n{other.n}, cap{other.cap}, theVector{static_cast<T*>(operator new(cap * sizeof(T)))} {
  try {
    uninitialized_copy(other.begin(), other.end(), theVector);
  }
  catch(...) {
    operator delete(theVector);
    throw;
  }
}

template <typename T> vector<T>::vector(std::initializer_list<T> init): n{init.size()}, cap{init.size()}, theVector{static_cast<T*>(operator new(cap * sizeof(T)))} {
  try {
    uninitialized_copy(init.begin(), init.end(), theVector);
  }
  catch(...) {
    operator delete(theVector);
    throw;
  }
}

template <typename T> void vector<T>::push_back(const T &x) {
  increaseCap();
  new (theVector + n) T{x};
  ++n;
}

template <typename T> void vector<T>::push_back(T &&x) {
  increaseCap();
  new (theVector + (n++)) T{std::move(x)};
}

template<typename T> template<typename... Args> void vector<T>::emplace_back(Args&&... args) {
  increaseCap();
  new (theVector + (n++)) T{std::forward<Args>(args)...};
}

template <typename T>void vector<T>::pop_back() { if (n) theVector[--n]->~T(); }

template <typename T>vector<T>::~vector() {
  for (size_t i = n-1; i < n; --i) theVector[i].~T();
  operator delete(theVector);
}

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
    T *newVec = static_cast<T*>(operator new (2 * cap * sizeof(T)));
    size_t i;
    try {
      for (i = 0; i < cap; ++i) new (newVec + i) T{theVector[i]};
      for (size_t j = 0; j < cap; ++j) theVector[j].~T();
      operator delete(theVector);
      theVector = newVec;
      cap *= 2;
    }
    catch(...) {
      for (size_t j = 0; j != i; ++j) newVec[j].~T();
      operator delete(newVec);
      throw;
    }
  }
}

template <typename T>std::ostream &operator<<(std::ostream &out, const vector<T> &v) {
  for (auto &n : v) out << n << ' ';
  return out;
}
}
#endif
