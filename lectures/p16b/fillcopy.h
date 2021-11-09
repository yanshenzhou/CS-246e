#ifndef FILLCOPY_H
#define FILLCOPY_H
template<typename T> void uninitialized_fill(T *start, T *finish, const T &x) {
  T *p;
  try {
    for (p = start; p != finish; ++p) new (static_cast<void*>(p)) T{x};
  }
  catch (...) {
    for (T *q = start; q != p; ++q) q->~T();
    throw;
  }
}

template<typename T> void uninitialized_copy(const T *start, const T *finish, T *target) {
  const T *p;
  T *t = target;
  try {
    for (p = start; p != finish; ++p, ++t)
      new (static_cast<void*>(t)) T{*p};
  }
  catch (...) {
    for (T *q = target; q != p; ++q) q->~T();
  }
}
#endif
