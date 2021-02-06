#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  struct record {
    int ticket_no;
  } db;

  struct flock lock;

  int fd;
  // struct rc record;

  fd = open("dbfile1", O_RDWR);
  // printf("Enter record number which you want to lock:");
  // scanf("%s", &record);
  // record1 locking
  lseek(fd, 2 * sizeof(db), SEEK_SET);
  read(fd, &db, sizeof(db));
  // lock setting
  lock.l_type = F_RDLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 2 * sizeof(db);
  lock.l_len = sizeof(db);
  lock.l_pid = getpid();

  printf("Before Enter into record 3 Critical sections\n");

  fcntl(fd, F_SETLKW, &lock);

  printf("Current ticket number:%d\n", db.ticket_no);
  // db3.ticket_no++;
  // lseek(fd, 2 * sizeof(db3), SEEK_SET);
  printf("Inside record 3 critical sections\n");
  // write(fd, &db3, sizeof(db3));
  printf("Enter to unlock record 3...\n");
  getchar();
  lock.l_type = F_UNLCK;
  fcntl(fd, F_SETLK, &lock);
  printf("uncloked record ...\n");
  printf("finish\n");
}
