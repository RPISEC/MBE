#include <stdio.h>
#include <string.h>
#define STDIN 0
//gcc -fstack-protector-all -mpreferred-stack-boundary=2 -o canary canary.c

void contrivedLeak() {
    char buf[512];
    scanf("%s", buf);
    printf(buf);
    return;
}

void contrivedOverflow() {
    printf("\n..I like to read ^_^ <==  ");
    char buf[24];
    read(STDIN, buf, 48);
    char lolz[24];
    strcpy(lolz, buf);
    printf(lolz);
    return;
}

int main(int argc, char* argv[]) {
    setbuf(stdout, NULL);
    printf("What you give, you will get back\n");
    printf("==> white elephants: ");
    contrivedLeak();
    printf("\nYou're lucky numbers are 512 and 1024\n");
    contrivedOverflow();
    printf("\n\nWoah There\n");
    return 0;

}
