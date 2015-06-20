/*
 *    Credit: https://defuse.ca/exploiting-cpp-vtables.htm
 */

#include <cstdlib>
#include <cstdio>
#include <cstring>

class CodeTester {
    public:
        virtual void test(const char*code)
        {
          int (*ret)() = (int(*)())code;
          ret();
        }
};

class CommandExecutor {
    public:
        virtual void execute(const char *command)
        {
            system(command);
        }
};

class Greeter {
    public:
        virtual void sayHello(const char *name)
        {
            printf("Hello, %s!\n", name);
        }
};

void greet(Greeter *greeter);
void doNothing();

int main(int argc, char **argv)
{
    Greeter g;
    char buf[64];
    printf("You must be 18 years or older to use this program. Are you? ");

    doNothing();

    gets(buf); /* OVERFLOW */
    if (strcmp(buf, "y") == 0) {
        greet(&g);
        return 0;
    } else {
        return 1;
    }
}

void greet(Greeter *greeter)
{
    char name[100];
    printf("What is your name? ");
    fgets(name, 100, stdin);
    name[strlen(name)-1] = '\0';
    greeter->sayHello(name);
}

/* This exists just so that the compiler/linker needs to include
 * CommandExecutor's code, since otherwise it would be unused. */
void doNothing()
{
    CommandExecutor e;
    CodeTester c;
}

