#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
extern char **environ;

int main() {
  printf("hello folks\n");
  if (execlp("/home/pilaniya/code/sslab/ls_RI.sh", "ls_RI.sh", NULL) == -1) {
    perror("execl()");
  }
}
