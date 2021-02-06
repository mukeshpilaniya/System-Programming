#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
extern char **environ;

int main() {
  printf("hello folks\n");
  if (execl("/home/pilaniya/code/sslab/a1.out", "a1.out", NULL) == -1) {
    perror("execl()");
  }
}
