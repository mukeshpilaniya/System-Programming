#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>
int main() {
  int fd;
  char filename[100];

  struct stat file;

  printf("Enter filename:");
  scanf("%s", filename);

  fd = open(filename, O_RDONLY);
  if (fd < 0) {
    printf("file can not open ....");
    exit(1);
  }
  if (fstat(fd, &file)) {
    printf("\nfstat error: [%s]\n", strerror(errno));
    close(fd);
    exit(1);
  }

  printf("I-node number: %ld\n", (long)file.st_ino);
  printf("Link count: %ld\n", (long)file.st_nlink);
  printf("Ownership: UID=%ld   GID=%ld\n", (long)file.st_uid,
         (long)file.st_gid);
  printf("Preferred I/O block size: %ld bytes\n", (long)file.st_blksize);
  printf("File size:%lld bytes\n", (long long)file.st_size);
  printf("Blocks allocated: %lld\n", (long long)file.st_blocks);
  printf("Last status change:       %s", ctime(&file.st_ctime));
  printf("Last file access:         %s", ctime(&file.st_atime));
  printf("Last file modification:   %s", ctime(&file.st_mtime));

  exit(EXIT_SUCCESS);
}
