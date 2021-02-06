#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

void main(void) {
  int fd;
  fd = mkfifo("MyFifoFile", 744);
  if (fd < 0) {
    perror("mkfifo()");
    exit(0);
  }
}
