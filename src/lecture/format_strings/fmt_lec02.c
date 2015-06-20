/*
 * Format Strings Example 2
 *
 */
#include <stdio.h>
#include <stdlib.h>

int
main(int argc, char *argv[])
{
  int unchangeable = 0xcafebabe;
  char buf[100];

  fgets(buf, 100, stdin);
  printf(buf);

  //HINT
  fprintf(stderr, "unchangeable @ %p\n", &unchangeable);

  //fgets makes it impossible to overflow the buffer,
  //  but just in case...
  if (unchangeable != 0xcafebabe) {
    printf("Cookie overwritten!\n");
    printf("unchangeable changed to %#x\n", unchangeable);
    exit(EXIT_FAILURE);
  }

  return EXIT_SUCCESS;
}
