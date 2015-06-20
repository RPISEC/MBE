#include <stdio.h>

int main()
{
    char buffer[128] = {0};

    /* break stuff */
    printf("insert ropchain: ");
    gets(buffer);
    
    /* program always returns 0 */
    return 0;
}
