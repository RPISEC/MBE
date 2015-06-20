/* doom doesn't mess around with his gcc protections, everything is on! */
/* compiled with: gcc -z relro -z now -fPIE -pie -fstack-protector-all -o heap_uaf heap_uaf.c */

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

struct toystr {
    void (* message)(char *);
    char buffer[20];
};

struct person {
    int favorite_num;
    int age;
    char name[16];
};

void print_cool(char * who)
{
    printf("%s is cool!\n", who);
}

void print_meh(char * who)
{
    printf("%s is meh...\n", who);
}

void secret_shell()
{
    execve("/bin/sh", NULL, NULL);
}

void print_menu()
{
    printf("-- Menu ----------------------\n"
           "1. Make coolguy\n"
           "2. Make a_person\n"
           "3. Delete coolguy\n"
           "4. Delete a_person\n"
           "5. Print coolguy message\n"
           "6. Print person info\n"
           "7. Quit\n"
           "Enter Choice: ");
}

/* bugs galore... but no memory corruption! */
int main(int argc, char * argv[])
{
    struct toystr * coolguy = NULL;
    struct person * a_person = NULL;
    int choice = 0;

    while(1)
    {
        print_menu();
        
        /* get menu option */
        scanf("%u", &choice);
        getc(stdin);

        /* perform menu actions */
        if(choice == 1)
        {
            coolguy = malloc(sizeof(struct toystr));
            printf("New coolguy is at 0x%08x\n", (unsigned int)coolguy);
            
            /* no memory corruption this time */
            printf("Input coolguy's name: ");
            fgets(coolguy->buffer, 20, stdin);
            coolguy->buffer[strcspn(coolguy->buffer, "\n")] = 0;
            coolguy->message = &print_cool;

            /* yay */
            printf("Created new coolguy!\n");
        }
        else if(choice == 2)
        {
            a_person = malloc(sizeof(struct person));
            printf("New person is at 0x%08x\n", (unsigned int)a_person);

            /* initialize a_person */
            printf("Input a_person's name: ");
            fgets(a_person->name, 16, stdin);
            a_person->name[strcspn(a_person->name, "\n")] = 0;
            
            printf("Input a_person's favorite number: ");
            scanf("%u", &a_person->favorite_num);
            getc(stdin);

            printf("Input a_person's age: ");
            scanf("%u", &a_person->age);
            getc(stdin);
            if(a_person->age > 110 || a_person->age < 0)
                printf("Wow your age is pretty crazy yo\n");

            /* all done here */
            printf("Created a new person!\n");
        }
        else if(choice == 3)
        {
            if(coolguy)
            {
                free(coolguy);
                printf("Deleted coolguy!\n");
            }
            else
                printf("There is no coolguy to free!\n");
        }
        else if(choice == 4)
        {
            if(a_person)
            {
                free(a_person);
                printf("Deleted person!\n");
            }
            else
                printf("There is no person to free!\n");
        }
        else if(choice == 5)
        {
            if(coolguy)
                coolguy->message(coolguy->buffer);
            else
                printf("There is no coolguy to print the cool message!\n");
        }
        else if(choice == 6)
        {
            if(a_person)
            {
                printf("Person's name: %s\n", a_person->name);
                printf("Person's age: %d\n", a_person->age);
                printf("Persons' favorite number: %u\n", a_person->favorite_num);
            }
            else
                printf("There is no person to print!\n");
        }
        else if(choice == 7)
            break;
        else
            printf("Invalid choice!\n");
      
        choice = 0;
    }

    printf("See you tomorrow!\n");
    return 0;
}
