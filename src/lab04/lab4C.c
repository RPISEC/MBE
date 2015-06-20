/*
 *   Format String Lab - C Problem
 *   gcc -z execstack -z norelro -fno-stack-protector -o lab4C lab4C.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define PASS_LEN 30

int main(int argc, char *argv[])
{
    char username[100] = {0};
    char real_pass[PASS_LEN] = {0};
    char in_pass[100] = {0};
    FILE *pass_file = NULL;
    int rsize = 0;

    /* open the password file */
    pass_file = fopen("/home/lab4B/.pass", "r");
    if (pass_file == NULL) {
        fprintf(stderr, "ERROR: failed to open password file\n");
        exit(EXIT_FAILURE);
    }

    /* read the contents of the password file */
    rsize = fread(real_pass, 1, PASS_LEN, pass_file);
    real_pass[strcspn(real_pass, "\n")] = '\0';  // strip \n
    if (rsize != PASS_LEN) {
        fprintf(stderr, "ERROR: failed to read password file\n");
        exit(EXIT_FAILURE);
    }

    /* close the password file */
    fclose(pass_file);

    puts("===== [ Secure Access System v1.0 ] =====");
    puts("-----------------------------------------");
    puts("- You must login to access this system. -");
    puts("-----------------------------------------");

    /* read username securely */
    printf("--[ Username: ");
    fgets(username, 100, stdin);
    username[strcspn(username, "\n")] = '\0';    // strip \n

    /* read input password securely */
    printf("--[ Password: ");
    fgets(in_pass, sizeof(in_pass), stdin);
    in_pass[strcspn(in_pass, "\n")] = '\0';      // strip \n

    puts("-----------------------------------------");

    /* log the user in if the password is correct */
    if(!strncmp(real_pass, in_pass, PASS_LEN)){
        printf("Greetings, %s!\n", username);
        system("/bin/sh");
    } else {
        printf(username);
        printf(" does not have access!\n");
        exit(EXIT_FAILURE);
    }

    return EXIT_SUCCESS;
}
