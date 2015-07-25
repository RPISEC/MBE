/* compiled with: gcc -z relro -z now -pie -fPIE -fno-stack-protector -o lab6B lab6B.c */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "utils.h"

ENABLE_TIMEOUT(300)

/* log the user in */
int login()
{
    printf("WELCOME MR. FALK\n");

    /* you win */
    system("/bin/sh");
    return 0;
}

/* doom's super secret password mangling scheme */
void hash_pass(char * password, char * username)
{
    int i = 0;

    /* hash pass with chars of username */
    while(password[i] && username[i])
    {
        password[i] ^= username[i];
        i++;
    }

    /* hash rest of password with a pad char */
    while(password[i])
    {
        password[i] ^= 0x44;
        i++;
    }

    return;
}

/* doom's super secure password read function */
int load_pass(char ** password)
{
    FILE * fd = 0;
    int fail = -1;
    int psize = 0;

    /* open the password file */
    fd = fopen("/home/lab6A/.pass", "r");
    if(fd == NULL)
    {
        printf("Could not open secret pass!\n");
        return fail;
    }

    /* get the size of the password */
    if(fseek(fd, 0, SEEK_END))
    {
        printf("Failed to seek to end of pass!\n");
        return fail;
    }

    psize = ftell(fd);

    if(psize == 0 || psize == -1)
    {
        printf("Could not get pass size!\n");
        return fail;
    }

    /* reset stream */
    if(fseek(fd, 0, SEEK_SET))
    {
        printf("Failed to see to the start of pass!\n");
        return fail;
    }

    /* allocate a buffer for the password */
    *password = (char *)malloc(psize);
    if(password == NULL)
    {
        printf("Could not malloc for pass!\n");
        return fail;
    }

    /* make sure we read in the whole password */
    if(fread(*password, sizeof(char), psize, fd) != psize)
    {
        printf("Could not read secret pass!\n");
        free(*password);
        return fail;
    }

    fclose(fd);

    /* successfully read in the password */
    return psize;
}

int login_prompt(int pwsize, char * secretpw)
{
    char password[32];
    char username[32];
    char readbuff[128];
    int attempts = -3;
    int result = -1;

    /* login prompt loop */
    while(attempts++)
    {
        /* clear our buffers to avoid any sort of data re-use */
        memset(password, 0, sizeof(password));
        memset(username, 0, sizeof(username));
        memset(readbuff, 0, sizeof(readbuff));

        /* safely read username */
        printf("Enter your username: ");
        fgets(readbuff, sizeof(readbuff), stdin);

        /* use safe strncpy to copy username from the read buffer */
        strncpy(username, readbuff, sizeof(username));

        /* safely read password */
        printf("Enter your password: ");
        fgets(readbuff, sizeof(readbuff), stdin);

        /* use safe strncpy to copy password from the read buffer */
        strncpy(password, readbuff, sizeof(password));

        /* hash the input password for this attempt */
        hash_pass(password, username);

        /* check if password is correct */
        if(pwsize > 16 && memcmp(password, secretpw, pwsize) == 0)
        {
            login();
            result = 0;
            break;
        }

        printf("Authentication failed for user %s\n", username);
    }

    return result;
}

int main(int argc, char* argv[])
{
    int pwsize;
    char * secretpw;

    disable_buffering(stdout);

    /* load the secret pass */
    pwsize = load_pass(&secretpw);
    pwsize = pwsize > 32 ? 32 : pwsize;

    /* failed to load password */
    if(pwsize == 0 || pwsize == -1)
        return EXIT_FAILURE;

    /* hash the password we'll be comparing against */
    hash_pass(secretpw, "lab6A");
    printf("----------- FALK OS LOGIN PROMPT -----------\n");
    fflush(stdout);

    /* authorization loop */
    if(login_prompt(pwsize, secretpw))
    {

        /* print the super serious warning to ward off hackers */
        printf("+-------------------------------------------------------+\n"\
               "|WARNINGWARNINGWARNINGWARNINGWARNINGWARNINGWARNINGWARNIN|\n"\
               "|GWARNINGWARNI - TOO MANY LOGIN ATTEMPTS - NGWARNINGWARN|\n"\
               "|INGWARNINGWARNINGWARNINGWARNINGWARNINGWARNINGWARNINGWAR|\n"\
               "+-------------------------------------------------------+\n"\
               "|       We have logged this session and will be         |\n"\
               "|  sending it to the proper CCDC CTF teams to analyze   |\n"\
               "|             -----------------------------             |\n"\
               "|     The CCDC cyber team dispatched will use their     |\n"\
               "|      masterful IT and networking skills to trace      |\n"\
               "|       you down and serve swift american justice       |\n"\
               "+-------------------------------------------------------+\n");

        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}
