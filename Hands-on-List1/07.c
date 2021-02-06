#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main() {
  FILE *ptr1, *ptr2;
  char c;
  char filename1[100], filename2[100];

  printf("Enter the filename:");
  scanf("%s", filename1);

  ptr1 = fopen(filename1, "r");
  if (ptr1 == NULL) {
    printf("file is not opened...");
    exit(1);
  }
  printf("Enter the filename for writing:");
  scanf("%s", filename2);
  ptr2 = fopen(filename2, "w");
  if (ptr2 == NULL) {
    printf("file is not opened...");
    exit(1);
  }
  c = fgetc(ptr1);
  while (c != EOF) {
    fputc(c, ptr2);
    c = fgetc(ptr1);
  }

  fclose(ptr1);
  fclose(ptr2);
}
