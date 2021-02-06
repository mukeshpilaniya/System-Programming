#include <stdio.h>
#include <unistd.h>

extern char **environ;

int main() {
  int i = 0;
  while (environ[i]) {
    printf("%s\n", environ[i++]);
  }
}
