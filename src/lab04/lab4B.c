/*
 *   Format String Lab - B Problem
 *   gcc -z execstack -z norelro -fno-stack-protector -o lab4B lab4B.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[])
{
    int i = 0;
    char buf[100];

    /* read user input securely */
    fgets(buf, 100, stdin);

    /* convert string to lowercase */
    for (i = 0; i < strlen(buf); i++)
        if (buf[i] >= 'A' && buf[i] <= 'Z')
            buf[i] = buf[i] ^ 0x20;

    /* print out our nice and new lowercase string */
    printf(buf);

    exit(EXIT_SUCCESS);
    return EXIT_FAILURE;
}
