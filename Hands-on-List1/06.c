#include <fcntl.h>
#include <stdio.h>
#include <string.h>
int main() {
  char buff[100];
  read(0, buff, 100);
  write(1, buff, strlen(buff));
  return 0;
}
