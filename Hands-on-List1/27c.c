#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
extern char **environ;
char *const envp[2] = {"PATH =/home/pilaniya/code/sslab", NULL};
int main() {
  printf("hello folks\n");
  if (execle("/home/pilaniya/code/sslab/ls_RI.sh", "ls_RI.sh", NULL, envp) ==
      -1) {
    perror("execl()");
  }
}
