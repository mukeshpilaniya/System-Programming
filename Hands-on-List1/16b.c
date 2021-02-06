#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/file.h>
#include <unistd.h>
int main() {
  int fd;
  struct flock f;

  fd = open("pilaniya", O_RDWR);
  if (fd < 0) {
    perror("open()");
  }

  f.l_type = F_WRLCK;
  f.l_whence = SEEK_SET;
  f.l_start = 0;
  f.l_len = 0;
  f.l_pid = getpid();
  printf("Before the file locked..\n");
  int lock = fcntl(fd, F_SETLKW, &f);
  if (lock < 0) {
    perror("fcntl");
  }
  printf("file is now locked\n Enter something to unlock\n");
  getchar();
  f.l_type = F_UNLCK;
  fcntl(fd, F_SETLK, &f);
  printf("file is unlocked now...\n");
}
