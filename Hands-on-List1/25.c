#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  int pid, pid1, pid2, pid3;
  pid_t childpid;
  int status;
  pid = getpid();
  printf("current process id: %d\n", pid);
  pid1 = fork();
  if (pid1 == 0) {
    sleep(4);
    printf("child 1 pid:%d and parent id:%d\n", getpid(), getppid());
  } else {
    pid2 = fork();
    if (pid2 == 0) {
      sleep(7);
      printf("child 2 pid:%d and parent id:%d\n", getpid(), getppid());
    } else {
      pid3 = fork();
      if (pid3 == 0) {
        sleep(20);
        printf("child 3 pid:%d and parent id:%d\n", getpid(), getppid());
      } else {
        sleep(12);
        printf("parent process id:%d\n", getpid());
        printf("Enter process is of child: ");
        scanf("%d", &childpid);
        waitpid(childpid, &status, WUNTRACED | WCONTINUED);
        if (WIFEXITED(status)) {
          printf("exited, status=%d\n", WEXITSTATUS(status));
        } else if (WIFSIGNALED(status)) {
          printf("killed by signal %d\n", WTERMSIG(status));
        } else if (WIFSTOPPED(status)) {
          printf("stopped by signal %d\n", WSTOPSIG(status));
        } else if (WIFCONTINUED(status)) {
          printf("continued\n");
        }
      }
    }
  }
}
