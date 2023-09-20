#ifndef TREE_H
#define TREE_H
#include <iostream>
#include "node.h"

/*
=========== Tree =========
This is the backend binary tree implientation, we use a head node
and a variable that holds the size. 
*/

namespace cs246e {

  class range_error{};

  template<typename K, typename V> class tree {
     size_t size; // <- variable holding the size
     node<K,V> *head;
    public:
     // Default construction of a tree
     tree(): size{0}, head{nullptr} {}

     // Updates each nodes index, such that every node that is greater then
     // the current key moves up one spot.
     void updateEntries (K key, node<K,V>* cur){
        if (cur != nullptr) {
            if (cur->compare(key) == 2) { cur->setEntry(cur->getEntry() + 1); }
            updateEntries(key, cur->left());
            updateEntries(key, cur->right());
        }
     }

     // Get the count of all the nodes that are less then the current key
     int getCountLess (K key) {
        int x = countNode (key, head);
        updateEntries(key, head);
        return x;
     }

     // Count all the nodes that are less
     int countNode (K key, node<K,V>* cur) {
        if (cur == nullptr) { return 0; }
        if (cur->compare(key) == 0) {
          return 1 + countNode(key, cur->left()) + countNode(key, cur->right());
        }
        return countNode(key, cur->left()) + countNode(key, cur->right());

     }

     // Finds the index of where a new node with that key should be and adds it
     void addNode(K key) {
       int ent = getCountLess(key);
       if (head == nullptr){
         head = new node<K,V>(key, ent);
         size = size + 1;
       } else {
         travToNode(key, head, ent);
       }
     }

     // Finds the index of a new node with and adds the new node there
     void addNode(K key, V value) {
        int ent = getCountLess(key);
        if (head == nullptr){
          head = new node<K,V>(key, value, ent);
          size = size + 1;
        } else {
          travToNode(key, value, head, ent);
        }

     }

     // Goes down the tree and adds the node such that the tree is balanced
     void travToNode(K key, node<K,V>* cur, int entry) {
        if (cur->right() == nullptr) {
           cur->setRight(key, entry);
           size = size + 1;
        } else if (cur->left() == nullptr) {
           cur->setLeft(key, entry);
           size = size + 1;
        } else {
           if (cur->leftCount() > cur->rightCount()){
              travToNode(key, cur->left(), entry);
           } else {
              travToNode(key, cur->right(), entry);
           }
        }
     }

     // Goes down the tree and adds the node such that the tree is balanced
     void travToNode(K key, V value, node<K,V>* cur, int entry){
        if (cur->right() == nullptr) {
           cur->setRight(key, value, entry);
           size = size + 1;
        } else if (cur->left() == nullptr) {
           cur->setLeft(key, value, entry);
           size = size + 1;
        } else {
           if (cur->leftCount() > cur->rightCount()){
              travToNode(key, value, cur->left(), entry);
           } else {
              travToNode(key, value, cur->right(), entry);
           }
        }
    }

    // Our destructor for the tree
    ~tree(){
       recDelete(head);
       head = nullptr;
    }

    // Loops through each nodes and delete it
    void recDelete(node<K,V>* cur) {
        if (cur != nullptr) {
           recDelete(cur->left());
           recDelete(cur->right());
           delete cur;
        }
    }

    // Get the data for the nth entry
    std::pair<K,V> &getNthPair(int n){
      node<K,V>* result = getNEntry(head, n);
      if (result == nullptr) { throw range_error{}; }
      else { return (result->getPair()); }
    }

    // Get the nth entires data
    V getNData(int n){
      node<K,V>* result = getNEntry(head, n);
      if (result == nullptr) { throw range_error{}; }
      else { return (result->getData()); }
    }

    // Get the nth entries key
    K getNKey(int n){
      node<K,V>* result = getNEntry(head, n);
      if (result == nullptr) { throw range_error{}; }
      else { return (result->getKey()); }
    }

    // Get the nth node
    node<K,V>* getNEntry(node<K,V>* cur, int entry){
      if (cur == nullptr) { return nullptr; }
      if (cur->getEntry() == entry) { return cur; }
      node<K,V> *left = getNEntry(cur->left(), entry);
      if (left != nullptr) { return left; }
      node<K,V> *right = getNEntry(cur->right(), entry);
      if (right != nullptr) { return right; }
      return nullptr;
    }

    // Get the size of the tree
    size_t getSize() {
       return (size);
    }

    // get the data of the node with the key
    V getData(K key){
       node<K,V>* result = findKey(head, key);
       if (result == nullptr) { throw range_error{}; }
       else { return (result->getData()); }
    }

    // return the reference of the data to the node with key
    V &getDataRef(K key) {
       node<K,V>* result = findKey(head, key);
       if (result == nullptr) { throw range_error{}; }
       else { return (result->getDataRef()); }
    }

    // Return the count of node with key
    int count(K queryKey){
       if (findKey(head, queryKey) == nullptr) { return 0; }
       return 1;
    }

    // Return the index of the element that needs to be deleted
    int delIndex(K queryKey){
       node<K,V>* result = findKey(head, queryKey);
       return (result->getEntry());
    }

    // Return the node with the node of key
    node<K,V>* findKey(node<K,V>* curNode, K key) {
       if (curNode == nullptr) { return nullptr; }
       if (curNode->getKey() == key) { return curNode; }
       node<K,V>* left = findKey(curNode->left(), key);
       if (left != nullptr) { return left; }
       node<K,V>* right = findKey(curNode->right(), key);
       if (right != nullptr) { return right; }
       return nullptr;
    }

    // DEBUG COMMAND for printing the tree
    void print(){
       printNode(head);
    }

    void printNode(node<K,V> *currNode){
       if (currNode != nullptr){
          currNode->print();
          printNode(currNode->left());
          printNode(currNode->right());
       }
    }


  };
}
#endif

