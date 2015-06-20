#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"

#define STORAGE_SIZE 100

/* gcc -Wall -z execstack -o lab3A lab3A.c */

/* get a number from the user and store it */
int store_number(unsigned int * data)
{
    unsigned int input = 0;
    unsigned int index = 0;

    /* get number to store */
    printf(" Number: ");
    input = get_unum();

    /* get index to store at */
    printf(" Index: ");
    index = get_unum();

    /* make sure the slot is not reserved */
    if(index % 3 == 0 || (input >> 24) == 0xb7)
    {
        printf(" *** ERROR! ***\n");
        printf("   This index is reserved for quend!\n");
        printf(" *** ERROR! ***\n");

        return 1;
    }

    /* save the number to data storage */
    data[index] = input;

    return 0;
}

/* returns the contents of a specified storage index */
int read_number(unsigned int * data)
{
    unsigned int index = 0;

    /* get index to read from */
    printf(" Index: ");
    index = get_unum();

    printf(" Number at data[%u] is %u\n", index, data[index]);

    return 0;
}

int main(int argc, char * argv[], char * envp[])
{
    int res = 0;
    char cmd[20] = {0};
    unsigned int data[STORAGE_SIZE] = {0};

    /* doom doesn't like enviroment variables */
    clear_argv(argv);
    clear_envp(envp);

    printf("----------------------------------------------------\n"\
           "  Welcome to quend's crappy number storage service!  \n"\
           "----------------------------------------------------\n"\
           " Commands:                                          \n"\
           "    store - store a number into the data storage    \n"\
           "    read  - read a number from the data storage     \n"\
           "    quit  - exit the program                        \n"\
           "----------------------------------------------------\n"\
           "   quend has reserved some storage for herself :>    \n"\
           "----------------------------------------------------\n"\
           "\n");


    /* command handler loop */
    while(1)
    {
        /* setup for this loop iteration */
        printf("Input command: ");
        res = 1;

        /* read user input, trim newline */
        fgets(cmd, sizeof(cmd), stdin);
        cmd[strlen(cmd)-1] = '\0';

        /* select specified user command */
        if(!strncmp(cmd, "store", 5))
            res = store_number(data);
        else if(!strncmp(cmd, "read", 4))
            res = read_number(data);
        else if(!strncmp(cmd, "quit", 4))
            break;

        /* print the result of our command */
        if(res)
            printf(" Failed to do %s command\n", cmd);
        else
            printf(" Completed %s command successfully\n", cmd);

        memset(cmd, 0, sizeof(cmd));
    }

    return EXIT_SUCCESS;
}
