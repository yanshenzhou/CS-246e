#ifndef VECTOR_H
#define VECTOR_H
#include <ostream>
#include <cstddef>
namespace cs246e {
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

     class reverse_iterator {
         int *it;
       public:
         reverse_iterator (int *it): it{it} {}
         bool operator!=(const reverse_iterator &other) const{
            return it != other.it;
         }
         int &operator*() { return *it; }
         reverse_iterator &operator++(){
           it--;
           return *this;
         }
     };

     reverse_iterator rbegin() {return reverse_iterator{theVector + n - 1}; }
     reverse_iterator rend() {return reverse_iterator{theVector - 1}; }

     class const_reverse_iterator {
         int *it;
       public:
         const_reverse_iterator (int *it): it{it} {}
         bool operator != (const const_reverse_iterator &other) const{
           return it != other.it;
         }
         const int &operator*() { return *it; }
         const_reverse_iterator &operator++(){
           it--;
           return *this;
         }
     };

     const_reverse_iterator rbegin() const {return const_reverse_iterator{theVector + n - 1}; }
     const_reverse_iterator rend() const {return const_reverse_iterator{theVector -1}; }

  private:
     void increaseCap();
  };

  std::ostream &operator<<(std::ostream &out, const vector &v);
}
#endif


