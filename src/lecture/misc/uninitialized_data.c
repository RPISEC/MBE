#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_USER 1024
#define MAX_PASS MAX_USER
#define ERR_CRITIC 0x01
#define ERR_AUTH 0x02

void escape(char* cmd)
{
	system(cmd);
}

int do_auth(void)
{
	char username[MAX_USER], password[MAX_PASS];
	fprintf(stdout, "Please enter your username: ");
	fgets(username, MAX_USER, stdin);
	fflush(stdin);
	fprintf(stdout, "Please enter your password: ");
	fgets(password, MAX_PASS, stdin);
#ifdef DEBUG
	fprintf(stderr, "Username is at: 0x%08x (%d)\n", &username, strlen(username));
	fprintf(stderr, "Password is at: 0x%08x (%d)\n", &password, strlen(password));
#endif
	if(!strcmp(username, "user") && !strcmp(password, "washere"))
	{
		return 0;
	}
	return -1;
}
int log_error(int farray, char *msg)
{
	char *err, *mesg;
	char buffer[24];
#ifdef DEBUG
	fprintf(stderr, "Mesg is at: 0x%08x\n", &mesg);
	fprintf(stderr, "Mesg is pointing at: 0x%08x\n", mesg);
#endif
	memset(buffer, 0x00, sizeof(buffer));
	sprintf(buffer, "Error: %s", mesg);
	fprintf(stdout, "%s\n", buffer);
	return 0;
}
int main(void)
{
	switch(do_auth())
	{
		case -1:
			log_error(ERR_CRITIC | ERR_AUTH, "Unable to login");
			break;
		default:
			break;
	}
	return 0;
}
