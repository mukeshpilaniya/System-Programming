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
  } db, db1;

  db.ticket_no = 10;
  fd = open("dbfile", O_CREAT | O_RDWR, 0744);
  write(fd, &db, sizeof(db));
  close(fd);
  fd = open("dbfile", O_RDONLY);
  read(fd, &db1, sizeof(db1));
  printf("Ticket no:%d\n", db1.ticket_no);
  close(fd);
}
