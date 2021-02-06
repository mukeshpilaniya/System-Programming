#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd;
  fd = open("pilaniya", O_WRONLY | O_APPEND);
  int status = fcntl(fd, F_GETFL);
  // 00000011 O_ACCMODE
  // printf("%d\n", O_ACCMODE);
  // printf("%d\n", O_WRONLY);
  // printf("%d\n", O_RDONLY);
  // printf("%d\n", O_RDWR);
  int fileStatus = status & O_ACCMODE;
  printf("%d\n", status);
  if (status < 0) {
    perror("fcntl");
  }
  if (fileStatus == O_RDWR) {
    printf("file is readable and writable\n");
  } else if (fileStatus == O_RDONLY) {
    printf("file is readable only\n");
  } else if (fileStatus == O_WRONLY) {
    printf("file is writable only\n");
  }
  // write(fd, "check file status\n", sizeof("check file status\n"));
}
