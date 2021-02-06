#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
int main() {
  int fd1, fd2;

  fd1 = open("filename1", O_RDWR | O_APPEND);
  if (fd1 < 0) {
    perror("open()");
  }
  fd2 = dup(fd1);
  write(fd1, "hello geeks\n", sizeof("hello geeks\n"));
  // printf("%d\n", fd2);
  write(fd2, "hello geeks\n", sizeof("hello geeks\n"));
  // printf("%d\n", dup(fd1));
}
