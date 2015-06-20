/*
 * gcc -z relro -z now -fPIE -pie -fstack-protector-all -o lab8B lab8B.c
 */

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_FAVES 10

struct vector {
	void (*printFunc)(struct vector*);
	char a;
	short b;
	unsigned short c;
	int d;
	unsigned int e;
	long f;
	unsigned long g;
	long long h;
	unsigned long long i;
};

struct vector v1;
struct vector v2;
struct vector v3;
struct vector* faves[MAX_FAVES];

void printVector(struct vector* v);

void printMenu()
{
	printf("+------------------------------------------------------------+\n");
	printf("|                                                            |\n");
	printf("|  1. Enter data                                          :> |\n");
	printf("|  2. Sum vectors                                         :] |\n");
	printf("|  3. Print vector                                        :3 |\n");
	printf("|  4. Save sum to favorites                               8) |\n");
	printf("|  5. Print favorites                                     :O |\n");
	printf("|  6. Load favorite                                       :$ |\n");
	printf("|  9. Get help                                            :D |\n");
	printf("|                                                            |\n");
	printf("+------------------------------------------------------------+\n");
	printf("I COMMAND YOU TO ENTER YOUR COMMAND: ");
}

struct vector* vectorSel()
{
	printf("Which vector? ");
	char sel;
	while((sel = getchar()) == '\n'); // I love C.
	switch(sel)
	{
		case '1':
			return &v1;
		case '2':
			return &v2;
		case '3':
			return &v3;
		default:
			printf("\nBAD VECTOR SELECTION\n");
			exit(EXIT_FAILURE);
	}
}

void enterData()
{
	struct vector* v = vectorSel();
	if(v == &v3)
	{
		printf("Please don't try to manually enter data into the sum.\n");
		return;
	}
	printf("Data entry time!\n");
	printf("char a: ");
	while((v->a = getchar()) == '\n'); // Still love C.
	printf("short b: ");
	scanf("%hd", &(v->b));
	printf("unsigned short c: ");
	scanf("%hu", &(v->c));
	printf("int d: ");
	scanf("%d", &(v->d));
	printf("unsigned int e: ");
	scanf("%u", &(v->e));
	printf("long f: ");
	scanf("%ld", &(v->f));
	printf("unsigned long g: ");
	scanf("%lu", &(v->g));
	printf("long long h: ");
	scanf("%lld", &(v->h));
	printf("unsigned long long i: ");
	scanf("%llu", &(v->i));
	v->printFunc = printVector;
}

void sumVectors()
{
	if(v1.a==0 || v2.a==0 ||
			v1.b==0 || v2.b==0 ||
			v1.c==0 || v2.c==0 ||
			v1.d==0 || v2.d==0 ||
			v1.e==0 || v2.e==0 ||
			v1.f==0 || v2.f==0 ||
			v1.g==0 || v2.g==0 ||
			v1.h==0 || v2.h==0 ||
			v1.i==0 || v2.i==0)
	{
		printf("You didn't even set the addends... :(\n");
		return;
	}
	v3.a = v1.a + v2.a;
	v3.b = v1.b + v2.b;
	v3.c = v1.c + v2.c;
	v3.d = v1.d + v2.d;
	v3.e = v1.e + v2.e;
	v3.f = v1.f + v2.f;
	v3.g = v1.g + v2.g;
	v3.h = v1.h + v2.h;
	v3.i = v1.i + v2.i;
	printf("Summed.\n");
}

/*
 * Bonus points if you don't use this function.
 */
void thisIsASecret()
{
	system("/bin/sh");
}

void printVector(struct vector* v)
{
	printf("Address: %p\n", v);
	printf("void printFunc: %p\n", v->printFunc);
	printf("char a: %c\n", v->a);
	printf("short b: %hd\n", v->b);
	printf("unsigned short c: %hu\n", v->c);
	printf("int d: %d\n", v->d);
	printf("unsigned int e: %u\n", v->e);
	printf("long f: %ld\n", v->f);
	printf("unsigned long g: %lu\n", v->g);
	printf("long long h: %lld\n", v->h);
	printf("unsigned long long i: %llu\n", v->i);
}

void fave()
{
	unsigned int i;
	for(i=0; i<MAX_FAVES; i++)
		if(!faves[i])
			break;
	if(i == MAX_FAVES)
		printf("You have too many favorites.\n");
	else
	{
		faves[i] = malloc(sizeof(struct vector));
		memcpy(faves[i], (int*)(&v3)+i, sizeof(struct vector));
		printf("I see you added that vector to your favorites, \
but was it really your favorite?\n");
	}
}

void printFaves()
{
	unsigned int i;
	for(i=0; i<MAX_FAVES; i++)
		if(faves[i])
			printVector(faves[i]);
		else
			break;
	printf("Printed %u vectors.\n", i);
}

void loadFave()
{
	printf("Which favorite? ");
	unsigned int i;
	scanf("%u", &i);
	if(i >= MAX_FAVES)
	{
		printf("Index out of bounds\n");
		return;
	}

	struct vector* v = vectorSel();
	if(v == &v3)
	{
		printf("Please don't try to manually enter data into the sum.\n");
		return;
	}
	memcpy(v, faves[i], sizeof(v));
}

void help()
{
	printf("\
This program adds two vectors together and stores it in a third vector. You \
can then add the sum to your list of favorites, or load a favorite back into \
one of the addends.\n");
}

int main(int argc, char** argv)
{
	char sel;
	printMenu();
	v1.printFunc = printf;
	v2.printFunc = printf;
	v3.printFunc = printf;
	struct vector* v;
	while((sel = getchar()) && (sel == '\n' || getchar())) // Magic ;^)
	{
		if(sel == '\n')
			continue;

		switch(sel)
		{
			case '0':
				printf("OK, bye.\n");
				return EXIT_SUCCESS;
			case '1':
				enterData();
				break;
			case '2':
				sumVectors();
				break;
			case '3':
				v = vectorSel();
				//printf("Calling %p\n", v->printFunc);
				v->printFunc(v);
				break;
			case '4':
				fave();
				break;
			case '5':
				printFaves();
				break;
			case '6':
				loadFave();
				break;
			case '9':
				help();
				break;
			default:
				printf("\nThat was bad input. \
Just like your futile attempt to pwn this.\n"); 
				return EXIT_FAILURE;
		}
		printMenu();
	}
	return EXIT_SUCCESS;
}
