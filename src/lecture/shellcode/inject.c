#include <stdio.h>

/* gcc -z execstack -fno-stack-protector -o inject inject.c */

int main()
{
    char buffer[128];

    puts("where we're going");
    puts("we don't need ... roads.");
    gets(buffer);
    
    return 0;
}

