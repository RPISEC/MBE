#include <stdlib.h>
#include <stdio.h>

/* gcc -fno-stack-protector -o lab5C lab5C.c */

char global_str[128];

/* reads a string, copies it to a global */
void copytoglobal()
{
    char buffer[128] = {0};
    gets(buffer);
    memcpy(global_str, buffer, 128);
}

int main()
{
    char buffer[128] = {0};

    printf("I included libc for you...\n"\
           "Can you ROP to system()?\n");

    copytoglobal();

    return EXIT_SUCCESS;
}
