#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
  int pid = getpid();
  printf("current process id: %d\n", pid);
  pid = fork();
  if (pid < 0) {
    perror("fork()");
  }
  if (pid == 0) {
    printf("child process id: %d\n", getpid());
    sleep(30);
    printf("orphan child parent id: %d\n", getppid());
  } else {
    printf("parent process completed\n");
    wait();
  }
}
