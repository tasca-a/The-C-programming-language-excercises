#include <stdio.h>

#define CHAR_LENGHT 26

int main(){

    int c;
    int character[CHAR_LENGHT];

    for (int i = 0; i < CHAR_LENGHT; i++)
        character[i] = 0;

    while((c = getchar()) != EOF){
        if (c >= 'A' && c <= 'Z')
            ++character[c - 'A'];
        if (c >= 'a' && c <= 'z')
            ++character[c - 'a'];
    }

    for (int i = 0; i < CHAR_LENGHT; i++){
            if (character[i] != 0){
            printf("\n%c:", i + 'A');
            for (int z = 0; z < character[i]; z++)
                putchar('=');
        }
    }
    putchar('\n');

    return 0;
}