#include <stdio.h>

/* gcc -static -o rop_pivot rop_pivot.c */

int main(int argc, char * argv[])
{
    char buffer[128] = {0};
    int overwrite[1] = {0};

    if(argc < 3)
    {
        printf("I need two arguments\n");
    	printf("Usage: %s [overwrite index] [overwrite address]\n", argv[0]);
        return 1;
    }

    /* create a pivot scenario */
    printf("Overwriting 0x%08x with 0x%08x\n", \
	overwrite[strtoul(argv[1], NULL, 10)], strtoul(argv[2], NULL, 10));
    overwrite[strtoul(argv[1], NULL, 10)] = strtoul(argv[2], NULL, 10);

    /* read a rop chain */
    printf("insert ropchain: ");
    fgets(buffer, 128, stdin);

    /* program always returns 0 */
    return 0;
}

