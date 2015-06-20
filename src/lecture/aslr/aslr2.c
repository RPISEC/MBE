/*
Exploitation with ASLR Enabled
Lecture: Example 2
Modern Binary Exploitation

Compiled with:
gcc -m32  -fno-stack-protector -z execstack -static ./aslr2.c

Patrick Biernat
*/


#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
    char my_string[16];
    char THE_TRICK[2] = "\xFF\xE4";

    fgets(my_string,40,stdin);
    
  
    return 0;
}
