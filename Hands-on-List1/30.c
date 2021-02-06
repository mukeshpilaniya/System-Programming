#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <syslog.h>
#include <unistd.h>

int main(void) {
  pid_t pid, sessionid;
  pid = fork();
  if (pid < 0) {
    exit(EXIT_FAILURE);
  }
  if (pid > 0) {
    exit(EXIT_SUCCESS);
  }
  umask(0);
  sessionid = setsid();
  if (sessionid < 0) {
    exit(EXIT_FAILURE);
  }
  if ((chdir("/home/pilaniya/code/sslab")) < 0) {
    exit(EXIT_FAILURE);
  }
  close(0);
  close(1);
  close(2);

  while (1) {
    sleep(2);
  }
  exit(EXIT_SUCCESS);
}
