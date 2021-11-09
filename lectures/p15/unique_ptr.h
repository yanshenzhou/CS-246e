#ifndef UNIQUE_PTR
#define UNIQUE_PTR
#include <utility>
namespace CS246E {
template <typename T> class unique_ptr {
  T *p;
 public:
  unique_ptr(T *p): p{p} {}
  ~unique_ptr() { delete p; }
  T *get() const { return p; }
  T *reset(T *ptr) {
    delete p;
    p = ptr;
  }
  T *release() {
    T *q = p;
    p = nullptr;
    return q;
  }
  T &operator*() const { return *p; }
  T *operator->() const { return p; }
  explicit operator bool() const { return p; }

  unique_ptr(const unique_ptr &other) = delete;
  unique_ptr &operator=(const unique_ptr &other) = delete;

  unique_ptr(unique_ptr &&other): p{other.p} { other.p = nullptr; }
  unique_ptr &operator=(unique_ptr &&other) {
    std::swap(p, other.p);
    return *this;
  }
};

template<typename T, typename... Args> unique_ptr<T> make_unique(Args&&... args) {
  return unique_ptr<T> { new T {std::forward<Args>(args)...}};
}
}
#endif
