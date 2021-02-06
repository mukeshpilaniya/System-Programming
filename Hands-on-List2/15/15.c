#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd[2];
  char buffer[512];
  pipe(fd);
  printf("pid of a parent process: %d\n", getpid());
  int pid = fork();
  if (pid < 0) {
    perror("fork()");
    exit(1);
  }
  if (pid > 0) {
    write(fd[1], "hello folks\n", sizeof("hello folks\n"));
  } else {
    read(fd[0], buffer, sizeof(buffer));
    printf("read by child pid %d: %s", getpid(), buffer);
  }
}
