#include "node.h"

size_t size(Node *n) {
  size_t count = 0;
  for (Node *cur = n; cur; cur = cur->next) ++count;
  return count;
}
