#ifndef VECTOR_H
#define VECTOR_H
#include <ostream>
#include <iostream>
#include <cstddef>
#include <initializer_list>
#include "fillcopy.h"
namespace CS246E {
class range_error{};

template <typename T> struct vector_base {
  size_t n, cap;
  T *v;
  vector_base(size_t n): n{n}, cap{n}, v{static_cast<T*>(operator new(n * sizeof(T)))} {}
  ~vector_base() { operator delete(v); }
};

template <typename T> class vector {
  static const size_t startSize = 1;
  vector_base<T> vb;
 public:
  vector();
  vector(size_t n, T i = T{});
  vector(const vector &other);
  vector(std::initializer_list<T> init);
  size_t size() const { return vb.n; }
  bool empty() const { return !vb.n; }
  const int &operator[](size_t i) const { return vb.v[i]; }
  T &operator[](size_t i) { return vb.v[i]; }
  void push_back(const T &x);
  void push_back(T &&x);
  void pop_back();
  ~vector();
  template <typename... Args> void emplace_back(Args&&... args);
  using iterator = T*;
  using const_iterator = const T*;

  iterator begin() { return vb.v; }
  iterator end() { return vb.v + vb.n; }

  const_iterator begin() const { return vb.v; }
  const_iterator end() const { return vb.v + vb.n; }

  T &at(size_t i);
  const T &at(size_t i) const;

 private:
  void increaseCap();
  void destroy_elements();
};

template <typename T> vector<T>::vector(): vb{startSize} { vb.n = 0; }

template <typename T> vector<T>::vector(size_t n, T i): vb{n?n:startSize} {
  if (n) uninitialized_fill(vb.v, vb.v + vb.n, i);
  else vb.n = 0;
}

template<typename T> vector<T>::vector(const vector &other): vb{other.cap} {
  if (other.n) uninitialized_copy(other.begin(), other.end(), vb.v);
  else vb.n = 0;
}

template <typename T> vector<T>::vector(std::initializer_list<T> init): vb{init.size()? init.size():startSize} {
  if (init.size()) uninitialized_copy(init.begin(), init.end(), vb.v);
  else vb.n = 0;
}

template <typename T> void vector<T>::push_back(const T &x) {
  emplace_back(x);
}

template <typename T> void vector<T>::push_back(T &&x) {
  emplace_back(std::move(x));
}

template<typename T> template<typename... Args> void vector<T>::emplace_back(Args&&... args) {
  increaseCap();
  new (vb.v + vb.n) T{std::forward<Args>(args)...};
  ++vb.n;
}

template <typename T>void vector<T>::pop_back() { if (vb.n) vb.v[--vb.n]->~T(); }

template <typename T>vector<T>::~vector() {
  destroy_elements();
}

template <typename T>T &vector<T>::at(size_t i) {
  if (i < vb.n) return vb.v[i];
  throw range_error{};
}

template <typename T>const T &vector<T>::at(size_t i) const {
  if (i < vb.n) return vb.v[i];
  throw range_error{};
}

template <typename T>void vector<T>::increaseCap() {
  if (vb.n == vb.cap) {
    vector_base<T> newVec{2 * vb.cap};
    newVec.n = vb.n;
    uninitialized_move_or_copy(vb.v, vb.v + vb.n, newVec.v);
    destroy_elements();
    std::swap(vb.v, newVec.v);
    std::swap(vb.cap, newVec.cap);
  }
}

template <typename T> void vector<T>::destroy_elements() {
  for (auto&& p : *this) p.~T();
}

template <typename T>std::ostream &operator<<(std::ostream &out, const vector<T> &v) {
  for (auto &n : v) out << n << ' ';
  return out;
}
}
#endif
