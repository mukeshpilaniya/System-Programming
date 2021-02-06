#include <sched.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  int fifomax = sched_get_priority_max(SCHED_FIFO);
  if (fifomax < 0) {
    perror("fifo()");
  }
  printf("max real time priority:%d\n", fifomax);
  int fifomin = sched_get_priority_min(SCHED_FIFO);
  if (fifomin < 0) {
    perror("fifo()");
  }
  printf("max real time priority:%d\n", fifomin);
}
