#ifndef DEQUE_H
#define DEQUE_H
#include <iostream>
#include "node.h"
#include <initializer_list>

/*
========== Deque ==========
Here is our Deque function, which works based off the
node class. Note that much like node we use min_idx and max_idx to
store which part of the array we are actually using
*/
namespace cs246e {
  template<typename T> class deque {

      node<T>** array; // <- Pointer to array of Node<T> pointers
      size_t n; // <- Stores the number of values stored
      int cap, min_idx, max_idx;

     public:

      /*
         =============== Constructors ===============
      */

      // Basic Constructor: makes a single node at index 2
      deque(): n{0}, cap{5}, min_idx{2}, max_idx{2} {
         static node<T> *init[5];
         init[2] = new node<T>();
         array = init;
      }

      // Copy Constructor: makes a single node at index 2, adds all the data from other to it
      deque(const deque &other): n{0}, cap{other.cap}, min_idx{2}, max_idx{2} {
         static node<T> *tmp[300];
         tmp[2] = new node<T>();
         for (int i = other.min_idx; i < other.max_idx; i ++){
            std::cout << "HI " << i << std::endl;
            std::cout << other.at(i) << std::endl;
         }

         cap = other.cap;
         array = tmp;
      }

      // Move constructor: Swaps the data, set the min and max indexes to the same
      deque(deque &&other): n{other.n}, cap{other.cap}, min_idx{other.min_idx}, max_idx{other.max_idx} {
         swap(array, other.array);
      }

      // Initializer list constructor: makes a single node at the second index, pushes back all the data in initializer_list
      deque(std::initializer_list<T> init): n{init.size()}, cap{static_cast<int>(init.size())+5}, min_idx{2}, max_idx{2} {
         static node<T> *s_list[300];
         node<T> *first = new node<T>();
         s_list[2] = first; // <- sets the second index to a node
         for (auto &val: init) {
            if (s_list[max_idx]->right_full()){ // if the current node is used up go to the next node
               max_idx = max_idx + 1;
               s_list[max_idx] = new node<T>();
            }
            s_list[max_idx]->add_right(val);
         }
         array = s_list;
      }

      /*
        =================== Assingment ===================
      */

      // Copy assigment: Makes a deep copy of every element in other
      deque<T> &operator=(deque<T> &other) {

         n = other.n;
         cap = other.cap;
         min_idx = 2;
         max_idx = 2;

         static node<T> *newData[300];
         newData[max_idx] = new node<T>();
         for (auto t: other) {
            if (newData[max_idx]->right_full()){
               max_idx = max_idx + 1;
               newData[max_idx] = new node<T>();
            }
            newData[max_idx]->add_right(t);
         }
         array = newData;
         return (*this);
      }

      // Move assigment: switches the data between other and the current object
      deque<T> &operator=(deque<T> &&other) {

         n = other.n;
         cap = other.cap;
         min_idx = 2;
         max_idx = 2;

         swap(array, other.array);
         return (*this);

      }


      /*
        ================== Required Functions ===========
      */

      ~deque() {
         array = nullptr;
      }

      size_t size() const { return n; }
      bool empty() { return n == 0; }

      void push_back(T val){
         n = n + 1;
         if(array[max_idx]->right_full()){ // Checks if the current node is full
            max_idx = max_idx + 1;
            array[max_idx] = new node<T>(); // Makes a new node one to the right
         }
         array[max_idx]->add_right(val); // Adds that value to the current node
      }
      void push_front(T val){
         n = n + 1;
         if(array[min_idx]->left_full()){ // Checks to see if the current node is full (left side)
            min_idx = min_idx - 1;
            array[min_idx] = new node<T>(); // Makes a new node one to the left
         }
         array[min_idx]->add_left(val); // Adds a value to the current node
      }

      void pop_front(){
         n = n - 1;
         if(array[min_idx]->empty()) { // Checks to see if the current node is empty
            min_idx = min_idx + 1;
         }
         array[min_idx]->remove_left(); // Removes the left most value

      }
      void pop_back(){
         n = n - 1;
         if(array[max_idx]->empty()) { // Checks to see if the current node is empty
            max_idx = max_idx - 1;
         }
         array[max_idx]->remove_right();

      }

      T at(size_t pos){
         for (int i = min_idx; i < max_idx; ++i) { // Loops through every filled node
            if (pos < array[i]->size()) { // Checks to see if the location we are looking for is in the ith node
               return(array[i]->getData(pos)); // Gets the data in the ith node
            }
            pos = pos - array[i]->size(); // Subtract all the size of elements from the position
         }
         return(array[max_idx]->getData(pos)); // Data must be in the last node (or not exist)
      }
      // Acts the same as "at" just returns a reference to the data rather then the data itself
      T &operator[](size_t pos) {
         for (int i = min_idx; i < max_idx; ++i) {
            if (pos < array[i]->size()) {
               return(array[i]->getRef(pos));
            }
            pos = pos - array[i]->size();
         }
         return(array[max_idx]->getRef(pos));
      }


      // The iterator, stores a reference to the data as well as the starting and ending index
      class iterator {
         node<T>** data;
         size_t loc; // Current element the iterator is on
         int start, end;
         iterator(node<T>** data, size_t loc, int s, int e): data{data}, loc{loc}, start{s}, end{e} {}
        public:
         bool operator!=(iterator other) { return (loc != other.loc); } // Compares locations of te two iterators
         T &operator*() {
            size_t sum = loc;
            for (int i = start; i < end; ++i){ // Works much like the at function, retuning the reference to the nth element
               if (sum < data[i]->size()){
                  return data[i]->getRef(sum);
               }
               sum -= data[i]->size();
            }
            return data[end]->getRef(sum);
         }
         iterator &operator++() { // Incriments the iterator by one
            loc = loc + 1;
            return *this;
         }

         friend class deque;

      };

      iterator begin() { return iterator{array, 0, min_idx, max_idx}; } // Start at the first element (idx 0)
      iterator end() { return iterator{array, n, min_idx, max_idx}; } // End one element past the last (n)

   };


}

#endif
