#ifndef MAP_H
#define MAP_H
#include <iostream>
#include <initializer_list>
#include "tree.h"

/*
============ Map ===========
Our implimentation of a dictionary, where we have a key <k>
and a value <v>. It uses an underlying bst found in tree.h
*/
namespace cs246e {
  template<typename K, typename V> class map {
     tree<K,V> *data; // <- The underlying bst
    public:

     /*
        ============ Constructors =============
     */

     // Default Constructor
     map<K,V>(): data{nullptr} { data = new tree<K,V>(); }

     // Initilizer List Constructor
     map<K,V>(std::initializer_list<std::pair<K,V>> init) {
        data = new tree<K,V>();
        for (auto &val: init){
           data->addNode(val.first, val.second);
        }
     }

     // Copy Constructor
     map<K,V>(map<K,V> &other) {
        data = new tree<K,V>();
        for (auto &val: other){
           data->addNode(val.first, val.second);
        }
     }

     // Move Constructor
     map<K,V>(map<K,V> &&other) {
        std::swap(data, other.data);
     }

     /*
        ========= Allocater ======
     */

     // Copy allocator
     map<K,V> &operator=(map<K,V> &other) {
        map<K,V> *tmp = new map<K,V>{other};
        std::swap(data, tmp->data);
        delete tmp;
        return *this;
     }

     // Move allocator
     map<K,V> &operator=(map<K,V> &&other) {
        std::swap(data, other.data);
        return *this;
     }

     /*
         ========= Destructor =========
     */

     // Call the tree's destructor
     ~map<K,V>() {
        delete data;
     }


     /*
        =========== Required Operators ==========
     */

     V &operator[](K key) {
       if (data->count(key) == 0) { // Check if a key exists
          data->addNode(key); // Make a new node
       }
       return (data->getDataRef(key)); // Return a reference to the node of a key
     }

     V at (K key) {
       return (data->getData(key)); // Searches for a key, throw an exception
     }

     bool empty() {
        return (data->getSize() == 0); // Checks to see if the tree is empty
     }

     size_t size() {
        return (data->getSize()); // Get the size
     }

     void clear() { // Deletes the tree and makes a new one
        delete data;
        data = new tree<K,V>();
     }

     int count(K key){ // Count the number of elements in the tree
        return (data->count(key));
     }

     void erase (const K &key){ // Erase the element with the given key
        tree<K,V> *tmp = new tree<K,V>();
        int indx = data->delIndex(key);
        for (iterator x = begin(); x != end(); ++x){
           if (x.getLocation() != indx) {
              tmp->addNode((*x).first, (*x).second);
           }
        }
        delete data;
        data = tmp;

     }

     class iterator {
        tree<K,V>* data;
        size_t loc;
        iterator(tree<K,V>* data, size_t loc): data{data}, loc{loc} {}
       public:
        bool operator!=(iterator other) { return (loc != other.loc); }
        std::pair<K,V> &operator*() {
          return (data->getNthPair(loc));
        }
        iterator &operator++() {
          loc = loc + 1;
          return *this;
        }

        K getKey(){ return (data->getNKey(loc)); }
        V getValue() { return (data->getNData(loc)); }
        int getLocation() { return (static_cast<int>(loc)); }


       friend class map;
     };

     iterator begin() { return iterator{data, 0}; }
     iterator end() { return iterator{data, data->getSize()}; }

     // Helpers

     void print() {
        std::cout << "====== tree =====" << std::endl;
        data->print();
     }


  };
}
#endif


