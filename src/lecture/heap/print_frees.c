/* compiled with: gcc -o print_frees print_frees.c */
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define LEN 15

void print_chunk(unsigned int * ptr)
{
    /* LOL MAGIC */
    int is_free = *((*(ptr-1) & ~7)/4 + (ptr-1)) & 1;
    
    if(is_free)
    {
        printf("[ prev - 0x%08x ][ size - 0x%08x ][ data buffer (0x%08x) ----> ... ] - Chunk 0x%08x - In use\n", \
                *(ptr-2),
                *(ptr-1),
                (unsigned int)ptr,
                (unsigned int)(ptr-2));
    }else{
        
        printf("[ prev - 0x%08x ][ size - 0x%08x ][ fd - 0x%08x ][ bk - 0x%08x ] - Chunk 0x%08x - Freed\n", \
                *(ptr-2),
                *(ptr-1),
                *ptr,
                *(ptr+1),
                (unsigned int)(ptr-2));
    }

}

int main()
{
    unsigned int * ptr[LEN];
    unsigned int lengths[] = {0, 4, 8, 16, 24, 32, 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384};
    int i;

    printf("mallocing...\n");
    for(i = 0; i < LEN; i++)
        ptr[i] = malloc(lengths[i]);
    
    for(i = 0; i < LEN; i++)
        print_chunk(ptr[i]);
   
    printf("\nfreeing every other chunk...\n");
    for(i = 0; i < LEN; i+=2)
        free(ptr[i]);

    for(i = 0; i < LEN-1; i++)
        print_chunk(ptr[i]);
    
    return 0;
}
