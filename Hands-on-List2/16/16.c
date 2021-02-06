
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd1[2], fd2[2];
  char buffer[512];
  pipe(fd1);
  pipe(fd2);
  printf("pid of a process: %d\n", getpid());
  if (!fork()) {
    while (1) {
      close(fd1[0]);
      printf("message to parent:");
      fgets(buffer, sizeof(buffer), stdin);
      write(fd1[1], buffer, sizeof(buffer));
      close(fd2[1]);
      read(fd2[0], buffer, sizeof(buffer));
      printf("message from parent:%s\n", buffer);
    }
  } else {
    while (1) {
      close(fd1[1]);
      read(fd1[0], buffer, sizeof(buffer));
      printf("meaage from child:%s\n", buffer);
      close(fd2[0]);
      printf("message to child:");
      fgets(buffer, sizeof(buffer), stdin);
      write(fd2[1], buffer, sizeof(buffer));
    }
  }
}
