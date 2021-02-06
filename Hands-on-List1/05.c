#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
int main() {
  int fd1, fd2, fd3, fd4, fd5;

  fd1 = creat("file1", 0744);
  if (fd1 < 0) {
    printf("file1 is not created");
    exit(1);
  }
  fd2 = creat("file2", 0744);
  if (fd2 < 0) {
    printf("file2 is not created");
    exit(1);
  }

  fd3 = creat("file3", 0744);
  if (fd3 < 0) {
    printf("file3 is not created");
    exit(1);
  }

  fd4 = creat("file4", 0744);
  if (fd4 < 0) {
    printf("file4 is not created");
    exit(1);
  }

  fd5 = creat("file5", 0744);
  if (fd5 < 0) {
    printf("file5 is not created");
    exit(1);
  }

  printf("file1 fd:%d\nfile2 fd:%d\nfile3 fd:%d\nfile4 fd:%d\nfile5 fd:%d\n",
         fd1, fd2, fd3, fd4, fd5);
  while (1)
    ;
}
