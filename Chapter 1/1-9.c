#include <stdio.h>

int main(){
    
    int c;
    int before;

    while ((c = getchar()) != '\n'){
        if (!(c == ' ' && before == ' '))
            putchar(c);

        before = c;
    }
}