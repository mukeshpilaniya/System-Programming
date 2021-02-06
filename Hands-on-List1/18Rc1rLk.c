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
  read(fd, &db, sizeof(db));
  // read(fd, &db8, sizeof(db8));
  //  read(fd, &db9, sizeof(db9));
  // lock setting
  lock.l_type = F_RDLCK;
  lock.l_whence = SEEK_SET;
  lock.l_start = 0;
  lock.l_len = sizeof(db);
  lock.l_pid = getpid();

  printf("Before Enter into record 1 Critical sections\n");

  fcntl(fd, F_SETLKW, &lock);
  printf("Inside record 1 critical sections\n");

  printf("Current ticket number:%d\n", db.ticket_no);
  // printf("Current ticket number:%d\n", db8.ticket_no);
  // printf("Current ticket number:%d\n", db9.ticket_no);
  // db7.ticket_no++;
  // lseek(fd, 0L, SEEK_SET);
  // write(fd, &db7, sizeof(db7));
  printf("Enter to unlock record 1...\n");
  getchar();
  lock.l_type = F_UNLCK;
  fcntl(fd, F_SETLK, &lock);
  printf("uncloked record ...\n");
  printf("finish\n");
}
