#ifndef NODE_H
#define NODE_H
#include <iostream>

/*
===== NODE =====
This class stored the array of 10 T elements, I wrote some
basic operations to make work on the deque easier.
*/
namespace cs246e {

  template<typename T> class node {

     int array_max = 4; // <- Stores the index of the largest elementt
     int array_min = 5; // <- Stores the index of the smallest element

     T data[10];

    public:

     node() {}

     // This constructor makes a deep copy of another node
     node(node *other): array_max{other->array_max}, array_min{other->array_min}, data{other->data} {
        for (int i = 0; i < 10; i++){
           data[i] = other->data[i];
        }
     }

     size_t size() { return (array_max - array_min + 1); }
     bool empty() { return (array_max - array_min + 1) == 0; }

     // Two functions which do the same job, but its useful to distingish whats returned
     T getData(int indx) { return data[array_min + indx]; }
     T &getRef(int indx) { return data[array_min + indx]; }

     // Checks to make sure out array_min / array_max are not going out of bounds
     bool left_full() { return (array_min <= 0); }
     bool right_full() { return (array_max >= 9); }

     /*
        Adds data to the "back" of the array, or the closest right index of the data array.
        This function assumes that there is space, I.E inside the deque you first checked that
        right_full() was not true;
     */
     void add_right(T val) {
        array_max = array_max + 1;
        data[array_max] = val;
     }
     // Does the same as add_right() just to the left. Requires that left_full() was checked before
     void add_left(T val) {
        array_min = array_min - 1;
        data[array_min] = val;
     }

     // Changes the min and max index so that it no longer accounts for the data that was removed.
     void remove_left() { array_min = array_min + 1; }
     void remove_right() { array_max = array_max -1; }

  };
}
#endif

