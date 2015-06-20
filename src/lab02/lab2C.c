#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 * compiled with:
 * gcc -O0 -fno-stack-protector lab2C.c -o lab2C
 */

void shell()
{
	printf("You did it.\n");
	system("/bin/sh");
}

int main(int argc, char** argv)
{
	if(argc != 2)
	{
		printf("usage:\n%s string\n", argv[0]);
		return EXIT_FAILURE;
	}

	int set_me = 0;
	char buf[15];
	strcpy(buf, argv[1]);

	if(set_me == 0xdeadbeef)
	{
		shell();
	}
	else
	{
		printf("Not authenticated.\nset_me was %d\n", set_me);
	}

	return EXIT_SUCCESS;
}
