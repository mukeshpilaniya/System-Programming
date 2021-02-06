#include <sched.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
struct sched_param sp;

int main() {
  pid_t pid = getpid();
  // #define SCHED_OTHER	0
  // #define SCHED_NORMAL	0
  // #define SCHED_FIFO		1
  // #define SCHED_RR		2
  // #define SCHED_BATCH	3
  switch (sched_getscheduler(pid)) {
    case SCHED_OTHER:
      printf("pid %d's current scheduling policy: SCHED_OTHER\n", getpid());
      printf("pid %d's current scheduling priority: 0\n", getpid());
      break;
    case SCHED_FIFO:
      printf("pid %d's current scheduling policy: SCHED_FIFO\n", getpid());
      printf("pid %d's current scheduling priority: 1\n", getpid());
      break;
    case SCHED_RR:
      printf("pid %d's current scheduling policy: SCHED_RR\n", getpid());
      printf("pid %d's current scheduling priority: 2\n", getpid());
      break;
    default:
      printf("unknown policy\n");
  }
  // if (getuid()) {
  //  printf("run program as root to change scheduler.\n");
  //  exit(0);
  //}
  //  sp.sched_priority = 10;
  // if (sched_setscheduler(pid, SCHED_RR, &sp) == -1) {
  // perror("sched_setscheduler()");
  //}
  int pr = nice(10);
  if (pr == -1) {
    perror("nice()");
  }
  printf("new nice:%d\n", pr);

  switch (sched_getscheduler(pid)) {
    case SCHED_OTHER:
      printf("pid %d's change scheduling policy: SCHED_OTHER\n", getpid());
      printf("pid %d's change scheduling priority: %d\n", getpid(),
             sp.sched_priority);
      break;
    case SCHED_FIFO:
      printf("pid %d's change scheduling policy: SCHED_FIFO\n", getpid());
      printf("pid %d's change scheduling priority: %d\n", getpid(),
             sp.sched_priority);
      break;
    case SCHED_RR:
      printf("pid %d's change scheduling policy: SCHED_RR\n", getpid());
      printf("pid %d's change scheduling priority: %d\n", getpid(),
             sp.sched_priority);
      break;
    default:
      printf("unknown policy\n");
  }
  while (1)
    ;
}
