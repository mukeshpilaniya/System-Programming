#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  int fd;
  fd = symlink("file", "NewSymlinkFile");
  if (fd < 0) {
    perror("symlink()");
    exit(0);
  }
}
