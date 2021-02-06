#include <stdio.h>

int main() {
  if (fork() == 0) {
    printf("child process id:%d\n", getpid());
  } else {
    printf("parent process id:%d\n", getpid());
  }
}
