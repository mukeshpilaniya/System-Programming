#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd, fd1;
  fd = open("pilaniya", O_RDWR | O_APPEND);
  dup2(fd, fd1);
  write(fd1, "hello budy\n", sizeof("hello budy\n"));
  //  while (1)
  //  ;
}
