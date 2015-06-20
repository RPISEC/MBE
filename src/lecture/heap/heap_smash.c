#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

struct toystr {
    void (* message)(char *);
    char buffer[20];
};

void print_super(char * who)
{
    printf("%s is superrr cool......\n", who);
}

void print_cool(char * who)
{
    printf("%s is cool!\n", who);
}

void print_meh(char * who)
{
    printf("%s is meh...\n", who);
}

int main(int argc, char * argv[])
{
    struct toystr * coolguy = NULL;
    struct toystr * lameguy = NULL;

    coolguy = malloc(sizeof(struct toystr));
    lameguy = malloc(sizeof(struct toystr));

    coolguy->message = &print_cool;
    lameguy->message = &print_meh;
  
    printf("Input coolguy's name: ");
    fgets(coolguy->buffer, 200, stdin);
    coolguy->buffer[strcspn(coolguy->buffer, "\n")] = 0;

    printf("Input lameguy's name: ");
    fgets(lameguy->buffer, 20, stdin);
    lameguy->buffer[strcspn(lameguy->buffer, "\n")] = 0;

    coolguy->message(coolguy->buffer);
    lameguy->message(lameguy->buffer);

    return 0;
}
