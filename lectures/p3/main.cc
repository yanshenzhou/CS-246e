#include "node.h"

int main() {
 Node *n = new Node;
  n->data = 3;
  n->next = nullptr;
  Node *n2 = new Node {3, nullptr};
  Node *n3 = new Node {4, new Node {5, nullptr}};

  delete n;
  delete n2->next;
  delete n2;

  while (n3) {
    Node *tmp = n3;
    n3 = n3->next;
    delete tmp;
  }
}
