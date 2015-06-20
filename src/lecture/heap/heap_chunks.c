/* compiled with: gcc -o heap_chunks heap_chunks.c */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LEN 15

void print_chunk(unsigned int * ptr, unsigned int len)
{
    
    printf("[ prev - 0x%08x ][ size - 0x%08x ][ data buffer (0x%08x) -------> ... ] - from malloc(%d)\n", \
            *(ptr-2),
            *(ptr-1),
            (unsigned int)ptr,
            len);
}

int main()
{
    unsigned int * ptr[LEN];
    unsigned int lengths[] = {0, 4, 8, 16, 24, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
    int i;

    /* malloc chunks, and them print their fields */
    printf("mallocing...\n");

    for(i = 0; i < LEN; i++)
        ptr[i] = malloc(lengths[i]);
    
    for(i = 0; i < LEN; i++)
        print_chunk(ptr[i], lengths[i]);
   
    return 0;
}
