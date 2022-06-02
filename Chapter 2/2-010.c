#include <stdio.h>

int lower(int c);

int main(){
    char test[] = "CIAO IO SONO UNA STRINGA TUTTA MAIUSCOLA";

    for (int i = 0; test[i] != '\0'; ++i)
        putchar(lower(test[i]));
    putchar('\n');

    return 0;
}

/* lower: convert c to lower case; ASCII only */
int lower(int c){
    return (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
}