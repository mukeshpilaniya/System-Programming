#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
  int fd = open("22file", O_CREAT | O_RDWR | O_APPEND, 0744);

  if (fork() == 0) {
    write(fd, "written by child process\n",
          sizeof("written by child process\n"));
  } else {
    write(fd, "written by parent process\n",
          sizeof("written by parent process\n"));
  }
}
