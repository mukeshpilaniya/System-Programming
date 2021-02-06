#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
extern char **environ;
char *const argv[1] = {NULL};
char *const envp[2] = {"PATH=/home/pilaniya/code/sslab/ls_RI.sh", NULL};
int main() {
  printf("hello folks\n");
  if (execvp("/home/pilaniya/code/sslab/ls_RI.sh", argv) == -1) {
    perror("execl()");
  }
}
