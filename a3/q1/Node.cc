#include <cstddef>
#include <ostream>

struct Node {
   int data;
   Node *left, *right;
   Node &operator=(const Node &other);
};

Node &Node::operator=(const Node &other) {
   if (this != &other) {
      Node *tmp = left;
      left = other.left ? new Node{*other.left} : nullptr;
      try {
         right = other.right ? new Node{*other.right} : nullptr;
         data = other.data;
      } catch (...) {
         left = tmp;
         throw;
      }
   }

   return *this;
}




