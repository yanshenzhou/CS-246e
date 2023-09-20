#ifndef NODE_H
#define NODE_H
#include <iostream>

/*
========= Node ========
This represents each data point inside the tree, it has references
to the nodes left and right to it. As well it has a field keeping track
of its relative location.
*/
namespace cs246e {
  template<typename K, typename V> class node {
     int entry; // <- relative location in tree
     std::pair<K,V> pairData; // <- Stores the left and right key
     node<K,V> *lnode;
     node<K,V> *rnode;
    public:
     node() {}
     // Creates a new node using only the key
     node(K key, int entry): entry{entry}, lnode{nullptr}, rnode{nullptr} { pairData.first = key; }
     // Creates a new node with key and value
     node(K key, V val, int entry): entry{entry}, lnode{nullptr}, rnode{nullptr} {
        pairData.first = key;
        pairData.second = val;
     }

     V getData() { return pairData.second; } // <- return the data
     V &getDataRef() { return pairData.second; } // <- return the reference to the data
     K getKey() { return pairData.first; } // <- returns the key data
     int getEntry() { return entry; } // <- returns the entry
     std::pair<K,V> &getPair() { return pairData; } // returns the reference to the pair

     // replace the value
     void setValue(V value){
       pairData.second = value;
     }

     void setEntry(int e) { entry = e; } // sets the entry

     // Function for comparing keys in a node
     int compare(K key) {
        if (key > pairData.first) { return 0; }
        if (key == pairData.first) { return 1; }
        return 2;
     }

     node<K,V> *left() { return lnode; } // get left node
     node<K,V> *right() { return rnode; } // get right node

     // Function for setting the left and right of this node
     void setLeft(K initKey, V initVal, int initEntry) {
        lnode = new node<K,V>(initKey, initVal, initEntry);
     }
     void setLeft(K initKey, int initEntry) {
        lnode = new node<K,V>(initKey, initEntry);
     }
     void setRight(K initKey, V initVal, int initEntry) {
        rnode = new node<K,V>(initKey, initVal, initEntry);
     }
     void setRight(K initKey, int initEntry) {
        rnode = new node<K,V>(initKey, initEntry);
     }

     // Count all the nodes on the left
     int leftCount(){
        return countNodes(lnode);
     }
     // Count all the node on the right
     int rightCount(){
        return countNodes(rnode);
     }

     // Given a node returns the count of all the nodes below it
     int countNodes(node<K,V> *query){
        if (query == nullptr) {
           return 0;
        }
        return (1 + countNodes(query->lnode) + countNodes(query->rnode));

     }

     // Print the contents of a node [used for debugging]
     void print() {
        std::cout << "Key: " << pairData.first << " | Value: " << pairData.second << " | Entry: " << entry;
        std::cout << " | Left: " << (lnode == nullptr ? "empty":"hasValue");
        std::cout << " | Right: " << (rnode == nullptr ? "empty":"hasValue");
        std::cout << std::endl;

     }

  };
}
#endif

