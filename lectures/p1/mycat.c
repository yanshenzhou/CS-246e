#include <stdio.h>

void echo(FILE *f) {
  for(int c = fgetc(f); c != EOF; c = fgetc(f)) putchar(c);
}

int main(int argc, char *argv[]) {
  if (argc == 1) echo(stdin);
  else {
    for (int i = 1; i < argc; ++i) {
      FILE *f = fopen(argv[i], "r");
      echo(f);
      fclose(f);
    }
  }
}
