/*
 * Tools for anti-debug/disasm
 */

/* throws off esp analysis to thwart hexrays */
#define deathrays \
    __asm__ volatile("push     %eax      \n"\
                     "xor      %eax, %eax\n"\
                     "jz       .+5       \n"\
                     ".word    0xC483    \n"\
                     ".byte    0x04      \n"\
                     "pop      %eax      \n");

/* clear argv to avoid shellcode */
#define clear_argv(_argv) \
    for (; *_argv; ++_argv) { \
        memset(*_argv, 0, strlen(*_argv)); \
    }
#define clear_envp(_envp) clear_argv(_envp)

/* disables IO buffering on the file descriptor */
#define disable_buffering(_fd) setvbuf(_fd, NULL, _IONBF, 0)

/* clears stdin up until newline */
void clear_stdin(void)
{
    char x = 0;
    while(1)
    {
        x = getchar();
        if(x == '\n' || x == EOF)
            break;
    }
}

/* gets a number from stdin and cleans up after itself */
unsigned int get_unum(void)
{
    unsigned int res = 0;
    fflush(stdout);
    scanf("%u", &res);
    clear_stdin();
    return res;
}

void prog_timeout(int sig)
{
  asm("mov $1, %eax;"
      "mov $1, %ebx;"
      "int $0x80");
}

#include <signal.h>
#define ENABLE_TIMEOUT(_time) \
  __attribute__ ((constructor)) void enable_timeout_cons() \
  { \
      signal(SIGALRM, prog_timeout); \
      alarm(_time); \
  }
