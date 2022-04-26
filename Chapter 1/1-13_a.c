#include <stdio.h>

#define IN 1
#define OUT 0

// I didn't even had to use arrays lol.

int main(){
    int c, state;
    int wordlenght = 0;
    int wordcount = 0;

    state = OUT;

    while((c = getchar()) != EOF){
        if (c == ' ' || c == '\t' || c == '\n'){
            state = OUT;
            ++wordcount;

            printf("Word %d: ", wordcount);
            for (int i = 0; i < wordlenght; i++)
                printf("=");
            printf("\n");

            wordlenght = 0;
        } else
        if (state == OUT){
            state = IN;
            ++wordlenght;
        } else {
            ++wordlenght;
        }
    }
}