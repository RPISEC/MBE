/* compiled with: gcc -static -z relro -z now -fstack-protector-all -o lab7A lab7A.c */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "utils.h"

ENABLE_TIMEOUT(60)

#define MAX_MSG    10
#define MAX_BLOCKS 32
#define BLOCK_SIZE 4

struct msg {
    void (* print_msg)(struct msg *);
    unsigned int xor_pad[MAX_BLOCKS];
    unsigned int message[MAX_BLOCKS];
    unsigned int msg_len;
};

struct msg * messages[MAX_MSG];

/* apply one time pad */
void encdec_message(unsigned int * message, unsigned int * xor_pad)
{
    int i = 0;
    for(i = 0; i < MAX_BLOCKS; i++)
        message[i] ^= xor_pad[i];
}

/* print information about the given message */
void print_message(struct msg * to_print)
{
    unsigned int i = 0;
    char * xor_pad;
    char * message;

    xor_pad = (char *)&to_print->xor_pad;
    message = (char *)&to_print->message;

    /* print the message's xor pad */
    printf("\nXOR Pad: \n"
           "-----------------------------------------\n");

    for(i = 0; i < BLOCK_SIZE*MAX_BLOCKS; i++)
    {
        printf("%02x", xor_pad[i] & 0xFF);
        if(i % 32 == 31)
            puts("");
    }

    /* print encrypted message */
    printf("\nEncrypted Message: \n"
           "-----------------------------------------\n");

    for(i = 0; i < BLOCK_SIZE*MAX_BLOCKS; i++)
    {
        printf("%02x", message[i] & 0xFF);
        if(i % 32 == 31)
            puts("");
    }

    puts("");
}

/* creates a message */
int create_message()
{
    int i, j;
    struct msg * new_msg = NULL;

    /* find a free message slot */
    for(i = 0; i < MAX_MSG; i++)
        if(messages[i] == NULL)
            break;

    /* make sure we actually found an empty slot */
    if(messages[i])
    {
        printf("-No message slots left!\n");
        return 1;
    }

    printf("-Using message slot #%u\n", i);

    /* initialize new message */
    new_msg = malloc(sizeof(struct msg));
    memset(new_msg, 0, sizeof(struct msg));
    new_msg->print_msg = &print_message;

    for(j = 0; j < MAX_BLOCKS; j++)
        new_msg->xor_pad[j] = rand();

    /* get the length of data the user intends to encrypt */
    printf("-Enter data length: ");

    new_msg->msg_len = get_unum();

    if(new_msg->msg_len == 0)
    {
        printf("-Message length must be greater than zero!\n");
        free(new_msg);
        return 1;
    }

    /* make sure the message length is no bigger than the xor pad */
    if((new_msg->msg_len / BLOCK_SIZE) > MAX_BLOCKS)
        new_msg->msg_len = BLOCK_SIZE * MAX_BLOCKS;

    /* read in the message to encrypt with the xor pad */
    printf("-Enter data to encrypt: ");
    read(0, &new_msg->message, new_msg->msg_len);

    /* encrypt message */
    encdec_message(new_msg->message, new_msg->xor_pad);

    /* save the new message to the global list */
    messages[i] = new_msg;

    return 0;
}

int edit_message()
{
    char numbuf[32];
    unsigned int i = 0;

    /* get message index to destroy */
    printf("-Input message index to edit: ");
    fgets(numbuf, sizeof(numbuf), stdin);
    i = strtoul(numbuf, NULL, 10);

    if(i >= MAX_MSG || messages[i] == NULL)
    {
        printf("-Invalid message index!\n");
        return 1;
    }

    printf("-Input new message to encrypt: ");

    /* clear old message, and read in a new one */
    memset(&messages[i]->message, 0, BLOCK_SIZE * MAX_BLOCKS);
    read(0, &messages[i]->message, messages[i]->msg_len);

    /* encrypt message */
    encdec_message(messages[i]->message, messages[i]->xor_pad);

    return 0;
}

/* free a secure message */
int destroy_message()
{
    char numbuf[32];
    unsigned int i = 0;

    /* get message index to destroy */
    printf("-Input message index to destroy: ");
    fgets(numbuf, sizeof(numbuf), stdin);
    i = strtoul(numbuf, NULL, 10);

    if(i >= MAX_MSG || messages[i] == NULL)
    {
        printf("-Invalid message index!\n");
        return 1;
    }

    /* destroy message */
    memset(messages[i], 0, sizeof(struct msg));
    free(messages[i]);
    messages[i] = NULL;

    return 0;
}

/* print a message at a select index */
int print_index()
{
    char numbuf[32];
    unsigned int i = 0;

    /* get message index to print */
    printf("-Input message index to print: ");
    fgets(numbuf, sizeof(numbuf), stdin);
    i = strtoul(numbuf, NULL, 10);

    if(i >= MAX_MSG || messages[i] == NULL)
    {
        printf("-Invalid message index!\n");
        return 1;
    }

    /* print the message of interest */
    messages[i]->print_msg(messages[i]);

    return 0;
}

/* the vulnerability is in here */
void print_menu()
{
    printf("+---------------------------------------+\n"
           "|        Doom's OTP Service v1.0        |\n"
           "+---------------------------------------+\n"
           "|------------ Services Menu ------------|\n"
           "|---------------------------------------|\n"
           "| 1. Create secure message              |\n"
           "| 2. Edit secure message                |\n"
           "| 3. Destroy secure message             |\n"
           "| 4. Print message details              |\n"
           "| 5. Quit                               |\n"
           "+---------------------------------------+\n");
}

int main()
{
    int choice = 0;
    srand(time(NULL));
    disable_buffering(stdout);

    while(1)
    {
        print_menu();

        /* get menu option */
        printf("Enter Choice: ");
        choice = get_unum();

        printf("-----------------------------------------\n");

        /* handle menu selection */
        if(choice == 1)
        {
            if(create_message())
                printf("-Failed to create message!\n");
            else
                printf("-Message created successfully!\n");
        }
        else if(choice == 2)
        {
            if(edit_message())
                printf("-Failed to edit message!\n");
            else
                printf("-Message has been successfully modified!\n");
        }
        else if(choice == 3)
        {
            if(destroy_message())
                printf("-Failed to destroy message!\n");
            else
                printf("-Message destroyed!\n");
        }
        else if(choice == 4)
        {
            if(print_index())
                printf("-Failed to print message!\n");
        }
        else if(choice == 5)
        {
            break;  // exit
        }
        else
            printf("-Invalid choice!\n");

        choice = 0;
        puts("");
    }

    printf("See you tomorrow!\n");
    return EXIT_SUCCESS;
}
