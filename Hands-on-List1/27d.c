#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
extern char **environ;
char *const argv[1] = {NULL};
int main() {
  printf("hello folks\n");
  if (execv("/home/pilaniya/code/sslab/ls_RI.sh", argv) == -1) {
    perror("execl()");
  }
}
