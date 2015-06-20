/*
Exploitation with ASLR Enabled
Lecture: Example 1
Modern Binary Exploitation

Compiled with:
gcc -pie -fPIE -fno-stack-protector -o aslr_leak1 aslr_leak1.c

-Patrick Biernat
*/
#include <stdio.h>
#include <stdlib.h>

void i_am_rly_leet() 
{
    printf("You found me!\nGood job!\n");
    return;
}

int main(int argc, char** argv)
{
    char my_string[16];
    printf("Win Func @ %p\n",i_am_rly_leet);
    fflush(stdout);
    fgets(my_string,40,stdin);
    
  
    return 0;
}
