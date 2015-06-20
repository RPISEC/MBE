#include <signal.h>
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/ptrace.h>
#include <sys/reg.h>
#include <sys/prctl.h>
#include <wait.h>
#include "utils.h"

ENABLE_TIMEOUT(60)

/* gcc -z execstack -fno-stack-protector -o lab3B lab3B.c */

/* hint: write shellcode that opens and reads the .pass file.
   ptrace() is meant to deter you from using /bin/sh shellcode */

int main()
{
    pid_t child = fork();
    char buffer[128] = {0};
    int syscall = 0;
    int status = 0;

    if(child == 0)
    {
        prctl(PR_SET_PDEATHSIG, SIGHUP);
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);

        /* this is all you need to worry about */
        puts("just give me some shellcode, k");
        gets(buffer);
    }
    else
    {
        /* mini exec() sandbox, you can ignore this */
        while(1)
        {
            wait(&status);
            if (WIFEXITED(status) || WIFSIGNALED(status)){
                puts("child is exiting...");
                break;
            }

            /* grab the syscall # */
            syscall = ptrace(PTRACE_PEEKUSER, child, 4 * ORIG_EAX, NULL);

            /* filter out syscall 11, exec */
            if(syscall == 11)
            {
                printf("no exec() for you\n");
                kill(child, SIGKILL);
                break;
            }
        }
    }

    return EXIT_SUCCESS;
}
