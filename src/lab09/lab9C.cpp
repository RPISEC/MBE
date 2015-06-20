/*
 *  compile: g++ -fstack-protector-all -z relro -z now ./lab9C.cpp -o lab9C
 *
 *  DSVector - A basic homwork implementation of std::vector
 *  This is a wrapper program to test it!
 */

#include <iostream>
#include <limits>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <unistd.h>
#include "utils.h"

ENABLE_TIMEOUT(60)

void
print_menu(void)
{
    printf("+------- DSVector Test Menu -------+\n"
           "| 1. Append item                   |\n"
           "| 2. Read item                     |\n"
           "| 3. Quit                          |\n"
           "+----------------------------------+\n");
}

template <class T>
class DSVector {
    public:
                     // I don't like indexing from 0, I learned VB.NET first.
        DSVector() : len(1), alloc_len(len+256) {}
        unsigned int size() { return len; }
        void append(T item);
                                            // No info leaks, either!
        T get(unsigned int index) { return (index < alloc_len ? vector_data[index] : -1); };
    private:
        unsigned int alloc_len;
        unsigned int len;
        // I was asleep during the dynamic sizing part, at least you can't overflow!
        T vector_data[1+256];
};

template <class T>
void
DSVector<T>::append(T item)
{
    // No overflow for you!
    if (len >= alloc_len) {
        std::cout << "Vector is full!" << std::endl;
        return;
    }
    vector_data[this->len++] = item;
}

int
main(int argc, char *argv[])
{
    DSVector<int> test1;
    unsigned int choice = 0;
    bool done = false;
    disable_buffering(stdout);

    while (!done) {
        print_menu();
        std::cout << "Enter choice: ";
        choice = get_unum();

        /* handle menu selection */
        switch (choice) {
        case 1:
            std::cout << "Enter a number: ";
            choice = get_unum();
            test1.append(choice);
            break;
        case 2:
            std::cout << "Choose an index: ";
            choice = get_unum();
            printf("DSVector[%d] = %d\n", choice, test1.get(choice));
            break;
        case 3:
            done = true;
            break;
        default:
            puts("Invalid choice!");
            break;
        }
    }

    return EXIT_SUCCESS;
}
