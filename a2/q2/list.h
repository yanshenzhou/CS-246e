#ifndef LIST_H
#define LIST_H
#include <cstddef>
#include <iostream>

namespace cs246e {
class list {
  struct Node {
    int data;
    Node *next;
    Node(int data, Node *next);
    Node(const Node &other);
    Node(Node &&other);
    Node &operator=(Node other);
    ~Node();
  };

  Node *theList = nullptr;
  size_t len = 0;

 public:
  list();
  list(const list &other);
  list(list &&other);
  list &operator=(list other);
  size_t size() const;
  list &push_front(int n);
  list &pop_front();
  int &operator[](size_t i);
  const int &operator[](size_t i) const;
  ~list();

  class iterator {
    Node *p;
    iterator(Node *p): p{p} {}
   public:
    bool operator!=(const iterator &other) const { return p != other.p; }
    int &operator*() const { return p->data; }
    iterator &operator++() {
      p = p->next;
      return *this;
    }
    friend class list;
  };

  iterator begin() { return iterator{theList}; }
  iterator end() { return iterator{nullptr}; }

  iterator insert(iterator posn, int x);

  class const_iterator {
    Node *p;
    const_iterator(Node *p): p{p} {}
   public:
    bool operator!=(const const_iterator &other) const { return p != other.p; }
    const int &operator*() const { return p->data; }
    const_iterator &operator++() {
      p = p->next;
      return *this;
    }
    friend class list;
  };

  const_iterator begin() const { return const_iterator{theList}; }
  const_iterator end() const { return const_iterator{nullptr}; }

  const_iterator cbegin() const { return const_iterator{theList}; }
  const_iterator cend()  const { return const_iterator{nullptr}; }


 private:
  int &get(size_t i) const;  // private helper
};

std::ostream &operator<<(std::ostream &out, const list &l);
}
#endif
