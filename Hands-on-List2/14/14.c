
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
  write(fd[1], "pilaniya", sizeof("pilaniya"));
  read(fd[0], buffer, sizeof(buffer));
  printf("%s", buffer);
}
