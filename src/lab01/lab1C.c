/*
Modern Binary Exploitation
Lab 1: Introduction to Reverse Engineering
LabC: Simple CrackMe

gcc -m32 ./labC.c
*/

#include <stdlib.h>
#include <stdio.h>

int main(int argc, char ** argv) {
    int input;

    printf("-----------------------------\n");
    printf("--- RPISEC - CrackMe v1.0 ---\n");
    printf("-----------------------------\n");
    printf("\nPassword: ");
    scanf("%d", &input);

    if (input == 0x149A) {
        printf("\nAuthenticated!\n");
        system("/bin/sh");
    }
    else {
        printf("\nInvalid Password!!!\n");
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
