/*
 * Format Strings Example 3
 *
 */
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
  int unchangeable = 0xdeadbeef;
  char buf[100];

  fgets(buf, 100, stdin);
  printf(buf);

  //HINT
  fprintf(stderr, "unchangeable @ %p\n", &unchangeable);

  if (unchangeable == 0xcafebabe) {
    printf("Success!\n");
  } else {
    printf("Failure!\n");
    printf("unchangeable is %#x", unchangeable);
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
