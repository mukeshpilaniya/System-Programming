#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/sysmacros.h>
#include <sys/types.h>
#include <time.h>

int main(int argc, char *argv[]) {
  struct stat sb;

  if (argc != 2) {
    fprintf(stderr, "Usage: %s <pathname>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  if (lstat(argv[1], &sb) == -1) {
    perror("lstat");
    exit(EXIT_FAILURE);
  }

  printf("ID of containing device:  [%lx,%lx]\n", (long)major(sb.st_dev),
         (long)minor(sb.st_dev));

  printf("File type:                ");
  switch (sb.st_mode & S_IFMT) {
    case S_IFBLK:
      printf("block device\n");
      break;
    case S_IFCHR:
      printf("character device\n");
      break;
    case S_IFDIR:
      printf("directory\n");
      break;
    case S_IFIFO:
      printf("FIFO/pipe\n");
      break;
    case S_IFLNK:
      printf("symlink\n");
      break;
    case S_IFREG:
      printf("regular file\n");
      break;
    case S_IFSOCK:
      printf("socket\n");
      break;
    default:
      printf("unknown?\n");
      break;
  }
}
