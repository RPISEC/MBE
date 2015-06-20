/* compiled with: gcc -o sizes sizes.c */

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{

    unsigned int lengths[] = {32, 4, 20, 0, 64, 32, 32, 32, 32, 32};
    unsigned int * ptr[10];
    int i;
   
    /* make arbitrary chunks on the heap */
    for(i = 0; i < 10; i++)
        ptr[i] = malloc(lengths[i]);
   
    /* print distance between chunks, eg size of chunks */
    for(i = 0; i < 9; i++)
        printf("malloc(%2d) is at 0x%08x, %3d bytes to the next pointer\n", 
                lengths[i],
                (unsigned int)ptr[i],
                (ptr[i+1]-ptr[i])*sizeof(unsigned int));
   

   return 0;
}
