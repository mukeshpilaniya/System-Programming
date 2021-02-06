#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
int main() {
  if (fork() > 0) {
    // printf("child process id:%d\n", getpid());
    sleep(30);
  } else {
    // printf("parent process id:%d\n", getpid());
    printf(
        "child process complete it's execution and it wait for parent process "
        "to complete\n");
    exit(0);
  }
}
