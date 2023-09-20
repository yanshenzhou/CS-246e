#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>
#include "node.h"
#include <initializer_list>

namespace cs246e {
  template<typename T> class deque {
      node<T>** array;
      size_t n;
      int cap, min_idx, max_idx;
     public:
      deque(): n{0}, cap{5}, min_idx{2}, max_idx{2} {
         static node<T> *init[5];
         node<T> *first = new node<T>();
         init[2] = first;
         array = init;
      }

      deque(deque &other){
         min_idx = 2;
         max_idx = 2;
         n = 0;
         static node<T> *tmp[300];
         tmp[2] = new node<T>();
         for (auto &val: other){
            n = n + 1;
            if (tmp[max_idx]->right_full()){
               max_idx = max_idx + 1;
               tmp[max_idx] = new node<T>();
            }
            tmp[max_idx]->add_right(val);
         }
         cap = other.cap;
         array = tmp;
      }

      deque(deque &&other){
         swap(array, other.array);
         min_idx = other.min_idx;
         max_idx = other.max_idx;
         n = other.n;
         cap = other.cap;
      }

      deque(std::initializer_list<T> init): n{init.size()}, cap{static_cast<int>(init.size())+5}, min_idx{2}, max_idx{2} {
         static node<T> *s_list[300];
         node<T> *first = new node<T>();
         s_list[2] = first;
         for (auto &val: init) {
            if (s_list[max_idx]->right_full()){
               max_idx = max_idx + 1;
               s_list[max_idx] = new node<T>();
            }
            s_list[max_idx]->add_right(val);
         }
         array = s_list;
      }

      size_t size() const { return n; }
      bool empty() { return n == 0; }

      void push_back(T val){
         n = n + 1;
         if(array[max_idx]->right_full()){
            max_idx = max_idx + 1;
            array[max_idx] = new node<T>();
         }
         array[max_idx]->add_right(val);
      }
      void push_front(T val){
         n = n + 1;
         if(array[min_idx]->left_full()){
            min_idx = min_idx - 1;
            array[min_idx] = new node<T>();
         }
         array[min_idx]->add_left(val);
      }
      void pop_front(){
         n = n - 1;
         if(array[min_idx]->empty()) {
            min_idx = min_idx + 1;
         }
         array[min_idx]->remove_left();

      }
      void pop_back(){
         n = n - 1;
         if(array[max_idx]->empty()) {
            max_idx = max_idx - 1;
         }
         array[max_idx]->remove_right();

      }

      T at(size_t pos){
         for (int i = min_idx; i < max_idx; i++) {
            if (pos < array[i]->size()) {
               return(array[i]->getData(pos));
            }
            pos = pos - array[i]->size();
         }
         return(array[max_idx]->getData(pos));
      }

      T &operator[](size_t pos) {
         for (int i = min_idx; i < max_idx; i++) {
            if (pos < array[i]->size()) {
               return(array[i]->getRef(pos));
            }
            pos = pos - array[i]->size();
         }
         return(array[max_idx]->getRef(pos));
      }

      deque<T> &operator=(deque<T> &other){
         static node<T> *newData[600];
         min_idx = 2;
         max_idx = 2;
         cap = other.cap;
         n = 0;
         newData[max_idx] = new node<T>();
         for (auto t: other){
            n = n + 1;
            if (newData[max_idx]->right_full()){
               max_idx = max_idx + 1;
               newData[max_idx] = new node<T>();
            }
            newData[max_idx]->add_right(t);
         }
         array = newData;
         return (*this);
      }

      deque<T> &operator=(deque<T> &&other){
         swap(array, other.array);
         min_idx = other.min_idx;
         max_idx = other.max_idx;
         n = other.n;
         cap = other.cap;
         return (*this);

      }

      class iterator {
         node<T>** data;
         size_t loc;
         int start, end;
         iterator(node<T>** data, size_t loc, int s, int e): data{data}, loc{loc}, start{s}, end{e} {}
        public:
         bool operator!=(iterator other) { return (loc != other.loc); }
         T &operator*() {
            size_t sum = loc;
            for (int i = start; i < end; ++i){
               if (sum < data[i]->size()){
                  return data[i]->getRef(sum);
               }
               sum -= data[i]->size();
            }
            return data[end]->getRef(sum);
         }

         iterator &operator++() {
            loc = loc + 1;
            return *this;
         }

         size_t loc_h() { return loc; }

         friend class deque;

      };

      iterator begin() { return iterator{array, 0, min_idx, max_idx}; }
      iterator end() { return iterator{array, n, min_idx, max_idx}; }

     private:
      void increaseCap();

   };


}

#endif
