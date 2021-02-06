#include <stdio.h>
#include <time.h>

int main() {
  clock_t t;
  t = clock();
  getpid();
  t = clock() - t;
  double time_taken = ((double)t) * 1000000 / CLOCKS_PER_SEC;
  printf("getpid() took %f microsecond to execute \n", time_taken);
  return 0;
}
