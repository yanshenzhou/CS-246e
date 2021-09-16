#ifndef NODE_H
#define NODE_H
#include <cstddef> // this gets us the size_t type

struct Node {
  int data;
  Node *next;
};

size_t size(Node *n);

#endif
