#include <cstddef>
#include <iostream>
#include <utility>
#include "list.h"
namespace cs246e {

list::Node::Node(int data, Node *next): data{data}, next{next} {}

list::Node::Node(const Node &other): data{other.data}, next{other.next? new Node{*other.next}: nullptr} {}

list::Node::Node(Node &&other): data{other.data}, next{other.next} {
  other.next = nullptr;
}

list::Node &list::Node::Node::operator=(Node other) {
  data = other.data;
  std::swap(next, other.next);
  return *this;
}

list::Node::~Node() { delete next; }

list::list() {}

list::list(const list &other): theList{other.theList ? new Node{*other.theList}: nullptr}, len{other.len} {}

list::list(list &&other): theList{other.theList}, len{other.len} {
  other.theList = nullptr;
  other.len = 0;
}

list &list::operator=(list other) {
  std::swap(theList, other.theList);
  std::swap(len, other.len);
  return *this;
}

size_t list::size() const { return len; }

list &list::push_front(int n) {
  theList = new Node{n, theList};
  ++len;
  return *this;
}

list &list::pop_front() {
  if (len) {
    Node *tmp = theList;
    theList = theList->next;
    tmp->next = nullptr;
    delete tmp;
    --len;
  }
  return *this;
}

int &list::operator[](size_t i) {
  return get(i);
}

const int &list::operator[](size_t i) const {
  return get(i);
}

int &list::get(size_t i) const {
  Node *cur = theList;
  for (size_t j = 0; j < i; ++j) cur = cur->next;
  return cur->data;
}

list::iterator list::insert(list::iterator posn, int x){
   /*
      We first check to see if the user wants to make an insertion
      at the start of the list.
   */
   if (posn != iterator{theList}) {
      Node *cur = theList;
       /*
         We will now check if the first element is valid
       */
      if (cur != nullptr) {
         /*
           We will now loop through the list until we find the 
           index we want to add at, or the end of the list
         */
         len++;
         while (cur->next != nullptr && iterator{cur->next} != posn){
            cur = cur->next;
         }
         /*
           We create a new Node pointing where the node that we are replacing
           at. We will then get the Node infront of posn to point at this new
           node. We will then return the position of the new node
         */
         Node *elem = new Node{x, cur->next};
         std::swap(cur->next, elem);
         return iterator{cur->next};
      } else {
         /*
            if we reach this location it can be assumed that the pointer
            (posn) refers to an invalid list, I.E a null pointer. In this
            case if we add a new Node to nullptr we might have memory erros
            so we just ignore it!
         */
         return posn;
      }
   } else {
      /*
        We will do what we did with push_back() and add the element to
        the front of the list.
      */
      len++;
      Node *elem = new Node{x,theList};
      theList = elem;
      return elem;
   }
}

list::~list() { delete theList; }

std::ostream &operator<<(std::ostream &out, const list &l) {
  for (auto &n: l) out << n << ' ';
  return out;
}
}
