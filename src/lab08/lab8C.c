/*
 * gcc -z relro -z now -fPIE -pie -fstack-protector-all -o lab8C lab8C.c
 */

#include<errno.h>
#include<fcntl.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<unistd.h>

struct fileComp {
	char fileContents1[255];
	char fileContents2[255];
	int cmp;
};

char* readfd(int fd)
{
	// Find length of file
	int size = lseek(fd, 0, SEEK_END);
	if(size >= 255)
	{
		printf("Your file is too big.\n");
		exit(EXIT_FAILURE);
	}
	// Reset fd to beginning of file
	lseek(fd, 0, SEEK_SET);
	// Allocate space for the file and a null byte
	char* fileContents = malloc((size+1) & 0xff);
	if(!fileContents)
	{
		printf("Could not allocate space for file contents\n");
		exit(EXIT_FAILURE);
	}
	// Read the file contents into the buffer
	int numRead = read(fd, fileContents, size & 0xff);
	return fileContents;
}

int getfd(char* arg)
{
	if(arg[0] != '-' || arg[1] != 'f' || arg[3] != '=')
	{
		printf("Invalid formatting in argument \"%s\"\n", arg);
		return -1;
	}

	int fd;
	if(arg[2] == 'n')
	{
		// O_NOFOLLOW means that it won't follow symlinks. Sorry.
		fd = open(arg+4, O_NOFOLLOW | O_RDONLY);
		if(fd == -1)
		{
			printf("File could not be opened\n");
			return -1;
		}
	}
	else if(arg[2] == 'd')
	{
		errno = 0;
		fd = atoi(arg+4);
	}
	else
	{
		printf("Invalid formatting in argument \"%s\"\n", arg);
		return -1;
	}

	return fd;
}

struct fileComp* comparefds(int fd1, int fd2)
{
	struct fileComp* fc = malloc(sizeof(struct fileComp));
	if(!fc)
	{
		printf("Could not allocate space for file contents\n");
		exit(EXIT_FAILURE);
	}

	strcpy(fc->fileContents1, readfd(fd1));
	strcpy(fc->fileContents2, readfd(fd2));
	fc->cmp = strcmp(fc->fileContents1, fc->fileContents2);
	return fc;
}

char* securityCheck(char* arg, char* s)
{
	if(strstr(arg, ".pass"))
		return "<<<For security reasons, your filename has been blocked>>>";
	return s;
}

int main(int argc, char** argv)
{
	if(argc != 3)
	{
		printf("Hi. This program will do a lexicographical comparison of the \
contents of two files. It has the bonus functionality of being \
able to process either filenames or file descriptors.\n");
		printf("Usage: %s {-fn=<filename>|-fd=<file_descriptor>} {-fn=<filename>|-fd=<file_descriptor>}\n", argv[0]);
		return EXIT_FAILURE;
	}

	int fd1 = getfd(argv[1]);
	int fd2 = getfd(argv[2]);
	if(fd1 == -1 || fd2 == -1)
	{
		printf("Usage: %s {-fn=<filename>|-fd=<file_descriptor>} {-fn=<filename>|-fd=<file_descriptor>}\n", argv[0]);
		return EXIT_FAILURE;
	}
	if(fd1 == 0 || fd2 == 0)
	{
		printf("Invalid fd argument.\n");
		printf("(We're still fixing some bugs with using STDIN.)\n");
		printf("Usage: %s {-fn=<filename>|-fd=<file_descriptor>} {-fn=<filename>|-fd=<file_descriptor>}\n", argv[0]);
		return EXIT_FAILURE;
	}

	struct fileComp* fc = comparefds(fd1, fd2);
	
	printf(
			"\"%s\" is lexicographically %s \"%s\"\n", 
			securityCheck(argv[1], fc->fileContents1),
			fc->cmp > 0 ? "after" : (fc->cmp < 0 ? "before" : "equivalent to"),
			securityCheck(argv[2], fc->fileContents2));

	return EXIT_SUCCESS;
}
