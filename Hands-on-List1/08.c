#include <stdio.h>
#include <stdlib.h>
int main() {
  char filename[100000];
  char display[1000000];
  FILE *ptr;

  printf("Enter file to be open: ");
  scanf("%s", filename);
  printf("\n");

  ptr = fopen(filename, "r");
  if (ptr == NULL) {
    printf("file is not opend..");
    exit(1);
  }
  char q[100];
  while (EOF != fscanf(ptr, "%[^\n] ", display)) {
    scanf("%c", q);
    printf("%s", display);
  }
  fclose(ptr);
}
