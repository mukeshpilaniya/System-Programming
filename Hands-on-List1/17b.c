#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  struct {
    int ticket_no;
  } db2;

  struct flock lock;

  int fd;

  fd = open("dbfile", O_RDWR);
  read(fd, &db2, sizeof(db2));

  lock.l_type = F_WRLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = 0;
  lock.l_pid = getpid();

  printf("Before Enter into Critical sections\n");

  fcntl(fd, F_SETLKW, &lock);

  printf("Current ticket number:%d\n", db2.ticket_no);
  db2.ticket_no++;
  lseek(fd, 0L, SEEK_SET);
  printf("Inside the critical sections\n");
  write(fd, &db2, sizeof(db2));
  printf("ENter to unlock...\n");
  getchar();
  lock.l_type = F_UNLCK;
  printf("uncloked...\n");
  fcntl(fd, F_SETLK, &lock);
  printf("finish\n");
}
