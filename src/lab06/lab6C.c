/*
Exploitation with ASLR
Lab C

 gcc -pie -fPIE -fno-stack-protector -o lab6C lab6C.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct savestate {
    char tweet[140];
    char username[40];
    int msglen;
} save;

void set_tweet(struct savestate *save );
void set_username(struct savestate * save);

/* debug functionality, not used in production */
void secret_backdoor()
{
    char cmd[128];

    /* reads a command and executes it */
    fgets(cmd, 128, stdin);
    system(cmd);

    return;
}

void handle_tweet()
{
    struct savestate save;

    /* Initialize our save state to sane values. */
    memset(save.username, 0, 40);
    save.msglen = 140;

    /* read a username and tweet from the user */
    set_username(&save);
    set_tweet(&save);

    printf(">: Tweet sent!\n");
    return;
}

void set_tweet(struct savestate *save )
{
    char readbuf[1024];
    memset(readbuf, 0, 1024);

    printf(">: Tweet @Unix-Dude\n");
    printf(">>: ");

    /* read a tweet from the user, safely copy it to struct */
    fgets(readbuf, 1024, stdin);
    strncpy(save->tweet, readbuf, save->msglen);

    return;
}

void set_username(struct savestate * save)
{
    int i;
    char readbuf[128];
    memset(readbuf, 0, 128);

    printf(">: Enter your username\n");
    printf(">>: ");

    /* Read and copy the username to our savestate */
    fgets(readbuf, 128, stdin);
    for(i = 0; i <= 40 && readbuf[i]; i++)
        save->username[i] = readbuf[i];

    printf(">: Welcome, %s", save->username);
    return;
}

int main(int argc, char * argv[])
{

    printf(
    "--------------------------------------------\n" \
    "|   ~Welcome to l33t-tw33ts ~    v.0.13.37 |\n" \
    "--------------------------------------------\n");

    /* make some tweets */
    handle_tweet();

    return EXIT_SUCCESS;
}
