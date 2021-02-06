
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int fd1[2], fd2[2];

  pipe(fd1);
  pipe(fd2);

  if (!fork()) {
    dup2(fd1[1], 1);
    close(fd1[0]);
    close(fd2[0]);
    close(fd2[1]);
    execlp("ls", "ls", "-Rl", NULL);
  } else {
    if (!fork()) {
      dup2(fd1[0], 0);
      dup2(fd2[1], 1);
      close(fd2[0]);
      close(fd1[1]);
      execlp("grep", "grep", "^d", NULL);
    } else {
      dup2(fd2[0], 0);
      close(fd1[0]);
      close(fd1[1]);
      close(fd2[1]);
      execlp("wc", "wc", "-l", NULL);
    }
  }
}
