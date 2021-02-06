#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd;

  struct {
    int ticket_no;
  } db1, db2, db3, db4, db5, db6;

  db1.ticket_no = 10;
  db2.ticket_no = 20;
  db3.ticket_no = 30;
  fd = open("dbfile1", O_CREAT | O_RDWR, 0744);
  write(fd, &db1, sizeof(db1));
  write(fd, &db2, sizeof(db2));
  write(fd, &db3, sizeof(db3));
  close(fd);
  fd = open("dbfile1", O_RDONLY);
  read(fd, &db4, sizeof(db1));
  read(fd, &db5, sizeof(db2));
  read(fd, &db6, sizeof(db3));
  printf("Ticket no:%d\n", db4.ticket_no);
  printf("Ticket no:%d\n", db5.ticket_no);
  printf("Ticket no:%d\n", db6.ticket_no);
  close(fd);
}
