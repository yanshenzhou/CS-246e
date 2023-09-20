#ifndef NODE_H
#define NODE_H
#include <iostream>

namespace cs246e {
  template<typename T> class node {
     int array_max = 4;
     int array_min = 5;
     T data[10];
    public:

     node() {}
     node(node *other): array_max{other->array_max}, array_min{other->array_min}, data{other->data} {
        for (int i = 0; i < 10; i++){
           data[i] = other->data[i];
        }
     }

     size_t size() { return (array_max - array_min + 1); }
     bool empty() { return (array_max - array_min + 1) == 0; }

     T getData(int indx) { return data[array_min + indx]; }
     T &getRef(int indx) { return data[array_min + indx]; }

     bool left_full() { return (array_min <= 0); }
     bool right_full() { return (array_max >= 9); }

     T min() { return data[array_min]; }
     T max() { return data[array_max]; }

     void add_right(T val) {
        array_max = array_max + 1;
        data[array_max] = val;
     }
     void add_left(T val) {
        array_min = array_min - 1;
        data[array_min] = val;
     }

     void remove_left() { array_min = array_min + 1; }
     void remove_right() { array_max = array_max -1; }

  };
}
#endif

