#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd = creat("Creatfile1", 0744);
  if (fd < 0) {
    perror("creat()");
  }
  printf("file descriptor value is=%d", fd);
}
