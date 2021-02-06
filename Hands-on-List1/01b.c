#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
int main() {
  int fd;
  fd = link("file", "NewHardlinkFile");
  if (fd < 0) {
    perror("link()");
  }
}
