#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd, fd1;
  fd = open("pilaniya", O_RDWR | O_APPEND);
  fd1 = fcntl(fd, F_DUPFD, 0);
  printf("file discriptor value: %d\n", fd1);
  if (fd1 < 0) {
    perror("fcntl");
  }
  write(fd1, "hello budy\n", sizeof("hello budy\n"));
}
