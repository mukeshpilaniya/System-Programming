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
  lseek(fd, sizeof(db), SEEK_SET);
  read(fd, &db, sizeof(db));
  // lock setting
  lock.l_type = F_RDLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = sizeof(db);
  lock.l_len = sizeof(db);
  lock.l_pid = getpid();

  printf("Before Enter into record 2 Critical sections\n");

  fcntl(fd, F_SETLKW, &lock);

  printf("Current ticket number:%d\n", db.ticket_no);
  // db2.ticket_no++;
  // lseek(fd, sizeof(db1), SEEK_SET);
  printf("Inside record 2 critical sections\n");
  // write(fd, &db2, sizeof(db2));
  printf("Enter to unlock record 2...\n");
  getchar();
  lock.l_type = F_UNLCK;
  fcntl(fd, F_SETLK, &lock);
  printf("uncloked record ...\n");
  printf("finish\n");
}
