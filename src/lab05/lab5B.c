#include <stdlib.h>
#include <stdio.h>

/* gcc -fno-stack-protector --static -o lab5B lab5B.c */

int main()
{

    char buffer[128] = {0};

    printf("Insert ROP chain here:\n");
    gets(buffer);

    return EXIT_SUCCESS;
}
