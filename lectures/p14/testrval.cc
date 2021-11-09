void f (int &&x) {}

void g() {
  int x = 1;
  f(x);
}
