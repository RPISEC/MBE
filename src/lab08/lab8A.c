#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "utils.h"
#define STDIN 0

//gcc -static -fstack-protector-all -mpreferred-stack-boundary=2 -o lab8A lab8A.c
int *global_addr;
int *global_addr_check;

// made so you can only read what we let you

void selectABook() {
    /* Our Apologies,the interface is currently under developement */
    char buf_secure[512];
    scanf("%s", buf_secure);
    printf(buf_secure);
    if(strcmp(buf_secure, "A") == 0){
        readA();
    }else if(strcmp(buf_secure,"F") == 0){
        readB();
    }else if(*buf_secure == '\x00'){
        readC();
    }else if(buf_secure == 1337){
        printf("\nhackers dont have time to read.\n");
        exit(EXIT_FAILURE);
    }else{
        printf("\nWhat were you thinking, that isn't a good book.");
        selectABook();
    }
    return;
}

void readA(){

    printf("\n\n*************************************************\n");
    printf("{|} Aristote's Metaphysics 350 B.C. Book VIII {|}\n");
    printf("*************************************************\n\n");
    printf("To return to the difficulty which has been stated with respect both to definitions and to numbers, what is the cause of their unity? In the case of all things which have several parts and in which the totality is not, as it were, a mere heap, but the whole is something beside the parts, there is a cause; for even in bodies contact is the cause of unity in some cases, and in others viscosity or some other such quality. And a definition is a set of words which is one not by being connected together, like the Iliad, but by dealing with one object.-What then, is it that makes man one; why is he one and not many, e.g. animal + biped, especially if there are, as some say, an animal-itself and a biped-itself? Why are not those Forms themselves the man, so that men would exist by participation not in man, nor in-one Form, but in two, animal and biped, and in general man would be not one but more than one thing, animal and biped? \n");

}

void readB(){

    printf("\n\n*************************************************\n");
    printf("{|} Aristote's Metaphysics 350 B.C. Book IVIZ {|}\n");
    printf("*************************************************\n\n");
    printf(

    "Clearly, then, if people proceed thus in their usual manner of definition and speech, they cannot explain and solve the difficulty. But if, as we say, one element is matter and another is form, and one is potentially and the other actually, the question will no longer be thought a difficulty. For this difficulty is the same as would arise if 'round bronze' were the definition of 'cloak'; for this word would be a sign of the definitory formula, so that the question is, what is the cause of the unity of 'round' and 'bronze'? The difficulty disappears, because the one is matter, the other form. What, then, causes this-that which was potentially to be actually-except, in the case of things which are generated, the agent? For there is no other cause of the potential sphere's becoming actually a sphere, but this was the essence of either. Of matter some is intelligible, some perceptible, and in a formula there is always an element of matter as well as one of actuality; e.g. the circle is 'a plane figure'. But of the things which have no matter, either intelligible or perceptible, each is by its nature essentially a kind of unity, as it is essentially a kind of being-individual substance, quality, or quantity (and so neither 'existent' nor 'one' is present in their definitions), and the essence of each of them is by its very nature a kind of unity as it is a kind of being-and so none of these has any reason outside itself, for being one, nor for being a kind of being; for each is by its nature a kind of being and a kind of unity, not as being in the genus 'being' or 'one' nor in the sense that being and unity can exist apart from particulars. \n");

}

void readC(){

    printf("\n\n*************************************************\n");
    printf("{|} Aristote's Metaphysics 350 B.C. Book MN9+ {|}\n");
    printf("*************************************************\n\n");
   printf(
    "Owing to the difficulty about unity some speak of 'participation', and raise the question, what is the cause of participation and what is it to participate; and others speak of 'communion', as Lycophron says knowledge is a communion of knowing with the soul; and others say life is a 'composition' or 'connexion' of soul with body. Yet the same account applies to all cases; for being healthy, too, will on this showing be either a 'communion' or a 'connexion' or a 'composition' of soul and health, and the fact that the bronze is a triangle will be a 'composition' of bronze and triangle, and the fact that a thing is white will be a 'composition' of surface and whiteness. The reason is that people look for a unifying formula, and a difference, between potency and complete reality. But, as has been said, the proximate matter and the form are one and the same thing, the one potentially, and the other actually. Therefore it is like asking what in general is the cause of unity and of a thing's being one; for each thing is a unity, and the potential and the actual are somehow one. Therefore there is no other cause here unless there is something which caused the movement from potency into actuality. And all things which have no matter are without qualification essentially unities. ");


}

void findSomeWords() {
    /* We specialize in words of wisdom */
    char buf[24];
    // to avoid the null
    global_addr = (&buf+0x1);
    // have to make sure no one is stealing the librarians cookies (they get angry)
    global_addr_check = global_addr-0x2;
    char lolz[4];

    printf("\n..I like to read ^_^ <==  ");
    read(STDIN, buf, 2048); // >> read a lot every day !

    if(((*( global_addr))^(*(global_addr_check))) != ((*( global_addr))^(0xdeadbeef))){
        printf("\n\nWoah There\n");
        // why are you trying to break my program q-q
        exit(EXIT_FAILURE);
    }

    // protected by my CUSTOM cookie - so soooo safe now
    return;
}

int main(int argc, char* argv[]) {

    disable_buffering(stdout);
    printf("\n\n\n");
    printf("**********************************************\n"\
           "{|}  Welcome to QUEND's Beta-Book-Browser  {|}\n"\
           "**********************************************\n"\
           "\n"
           "\t==> reading is for everyone <==\n"\
           "\t[+] Enter Your Favorite Author's Last Name: ");
    selectABook();

    printf("\n...please turn to page 394...\n");
    findSomeWords();

    printf("\n\t[===] Whew you made it !\n\n");
    return EXIT_SUCCESS;
}
