/*
Exploitation with ASLR enabled
Lab A

gcc -fpie -pie -fno-stack-protector -o lab6A ./lab6A.c

Patrick Biernat
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "utils.h"

struct uinfo {
    char name[32];
    char desc[128];
    unsigned int sfunc;
}user;


struct item {
    char name[32];
    char price[10];
}aitem;

struct item ulisting;

void write_wrap(char ** buf) {
    write(1, *buf, 8);
}

void make_note() {
    char note[40];
    printf("Make a Note About your listing...: ");
    gets(note);
}

void print_listing() {
    printf(
    "Here is the listing you've created: \n");
    if(*ulisting.name == '\x00') {
        return;
    }
    printf("Item: %s\n", ulisting.name);
    printf("Price: %s\n",ulisting.price);
}

void make_listing() {
    printf("Enter your item's name: ");
    fgets(ulisting.name, 31, stdin);
    printf("Enter your item's price: ");
    fgets(ulisting.price, 9, stdin);
}

void setup_account(struct uinfo * user) {
    char temp[128];
    memset(temp, 0, 128);
    printf("Enter your name: ");
    read(0, user->name, sizeof(user->name));
    printf("Enter your description: ");
    read(0, temp, sizeof(user->desc));
    strncpy(user->desc, user->name,32);
    strcat(user->desc, " is a ");

    memcpy(user->desc + strlen(user->desc), temp, strlen(temp));
}

void print_name(struct uinfo * info) {
    printf("Username: %s\n", info->name);
}

int main(int argc, char ** argv) {
    disable_buffering(stdout);
    struct uinfo  merchant;
    char choice[4];

    printf(
    ".-------------------------------------------------. \n" \
    "|  Welcome to l337-Bay                          + | \n"
    "|-------------------------------------------------| \n"
    "|1: Setup Account                                 | \n"
    "|2: Make Listing                                  | \n"
    "|3: View Info                                     | \n"
    "|4: Exit                                          | \n"
    "|-------------------------------------------------| \n" );

    // Initialize user info
    memset(merchant.name, 0, 32);
    memset(merchant.desc, 0 , 64);
    merchant.sfunc = (unsigned int)print_listing;

    //initialize listing
    memset(ulisting.name, 0, 32);
    memset(ulisting.price, 0, 10);

    while(1) {
        memset(choice, 0, 4);
        printf("Enter Choice: ");

        if (fgets(choice, 2, stdin) == 0) {
            break;
        }
        getchar(); // Eat the newline

        if (!strncmp(choice, "1",1)) {
            setup_account(&merchant);
        }
        if (!strncmp(choice, "2",1)) {
            make_listing();
        }
        if (!strncmp(choice, "3",1)) { // ITS LIKE HAVING CLASSES IN C!
            ( (void (*) (struct uinfo *) ) merchant.sfunc) (&merchant);
        }
        if (!strncmp(choice, "4",1)) {
            return EXIT_SUCCESS;
        }

    }


    return EXIT_SUCCESS;
}
