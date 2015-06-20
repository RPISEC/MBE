/* compiled with: gcc -z relro -z now -fPIE -pie -fstack-protector-all -o lab7C lab7C.c */
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include "utils.h"

#define MAX_STR 6
#define MAX_NUM 6

struct data {
    char reserved[8];
    char buffer[20];
    void (* print)(char *);
};

struct number {
    unsigned int reserved[6];               // implement later
    void (* print)(unsigned int);
    unsigned int num;
};

void small_str(char * a_str)
{
    printf("here's your lame string: %s\n", a_str);
}

void big_str(char * a_str)
{
    printf("nice big str yo: %s\n", a_str);
}

void small_num(unsigned int a_num)
{
    printf("not 1337 enough: %u\n", a_num);
}

void big_num(unsigned int a_num)
{
    printf("tite number dawg: %u\n", a_num);
}

void print_menu()
{
    printf("-- UAF Playground Menu ----------------------\n"
           "1. Make a string\n"
           "2. Make a number\n"
           "3. Delete a string\n"
           "4. Delete a number\n"
           "5. Print a string\n"
           "6. Print a number\n"
           "7. Quit\n"
           "---------------------------------------------\n"
           "Enter Choice: ");
}

/* bugs galore... but no memory corruption! */
int main(int argc, char * argv[])
{
    struct data * strings[MAX_STR] = {0};
    struct number * numbers[MAX_NUM] = {0};
    struct data * tempstr = NULL;
    struct number * tempnum = NULL;

    int strcnt = 0;
    int numcnt = 0;
    unsigned int choice = 0;
    unsigned int index = 0;

    while(1)
    {
        print_menu();

        /* get menu option */
        if((choice = get_unum()) == EOF)
            break;

        /* make a string */
        if(choice == 1)
        {
            if(strcnt < MAX_STR)
            {
                tempstr = malloc(sizeof(struct data));

                /* no memory corruption this time */
                printf("Input string to store: ");
                fgets(tempstr->buffer, 20, stdin);
                tempstr->buffer[strcspn(tempstr->buffer, "\n")] = 0;

                /* pick a print function */
                tempstr->print = strlen(tempstr->buffer) > 10 ? big_str : small_str;

                /* store the string to our master list */
                strings[++strcnt] = tempstr;
                printf("Created new string!\n");
            }
            else
                printf("Please delete a string before trying to make another!\n");
        }

        /* make a number */
        else if(choice == 2)
        {
            if(numcnt < MAX_NUM)
            {
                tempnum = malloc(sizeof(struct number));

                printf("Input number to store: ");
                tempnum->num = get_unum();

                /* pick a print function */
                tempnum->print = tempnum->num > 0x31337 ? big_num : small_num;

                /* store the number to our master list */
                numbers[++numcnt] = tempnum;
                printf("Created new number!\n");
            }
            else
                printf("Please delete a number before trying to make another!\n");
        }

        /* delete a string */
        else if(choice == 3)
        {
            if(strcnt && strings[strcnt])
            {
                free(strings[strcnt--]);
                printf("Deleted most recent string!\n");
            }
            else
                printf("There are no strings left to delete!\n");
        }

        /* delete a number */
        else if(choice == 4)
        {
            if(numcnt && numbers[numcnt])
            {
                free(numbers[numcnt--]);
                printf("Deleted most recent number!\n");
            }
            else
                printf("There are no numbers left to delete!\n");
        }

        /* print a string */
        else if(choice == 5)
        {
            printf("String index to print: ");
            index = get_unum();

            if(index < MAX_STR && strings[index])
                strings[index]->print(strings[index]->buffer);
            else
                printf("There is no string to print!\n");
        }

        /* print a number */
        else if(choice == 6)
        {
            printf("Number index to print: ");
            index = get_unum();

            if(index < MAX_NUM && numbers[index])
                numbers[index]->print(numbers[index]->num);
            else
                printf("There is no number to print!\n");
        }

        /* quit */
        else if(choice == 7)
            break;

        /* base case */
        else
            printf("Invalid choice!\n");

        index = 0;
        choice = 0;
        printf("\n");
    }

    printf("See you tomorrow!\n");
    return EXIT_SUCCESS;
}
