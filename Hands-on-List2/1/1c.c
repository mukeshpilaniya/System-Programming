
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>

void timer_handler(int signum) {
  static int count = 0;
  printf("timer expired %d times\n", ++count);
}

int timer_check(int elapstime) {
  struct sigaction sa;
  struct itimerval timer;

  memset(&sa, 0, sizeof(sa));
  sa.sa_handler = &timer_handler;
  sigaction(SIGVTALRM, &sa, NULL);

  timer.it_value.tv_sec = 2;
  timer.it_value.tv_usec = 0;
  timer.it_interval.tv_sec = elapstime;
  timer.it_interval.tv_usec = 0;

  setitimer(ITIMER_PROF, &timer, NULL);

  while (1)
    ;
}

int main() { timer_check(10); }
