#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd, fd1;
  char buff[10], buff1[10];
  fd = open("linebyline", O_RDONLY);
  fd1 = creat("nvidsce", 0744);
  if (fd < 0) {
    printf("File can not opend..\n");
    exit(1);
  }

  while (read(fd, buff, 10)) {
    printf("%s", buff);
    int byte1 = lseek(fd, 10, SEEK_CUR);
    // read(fd, buff, 10);
    // printf("%s", buff);
    write(fd1, buff, 10);
  }
}
