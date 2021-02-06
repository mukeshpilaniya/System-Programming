#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
int main() {
  int fd;
  fd = open("openfile1", O_CREAT, 0744);
  if (fd < 0) {
    perror("open()");
  }
  printf("file discriptor value: %d", fd);
}
