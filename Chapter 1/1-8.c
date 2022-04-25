#include <stdio.h>

int main(){
    
    int c;
    int blank, tab, nl;

    blank = 0;
    tab = 0;
    nl = 0;

    while((c = getchar()) != EOF){
        if (c == ' ')
            blank++;
        if (c == '\t')
            tab++;
        if (c == '\n')
            nl++;
    }

    printf("blanks: %d\ntabs: %d\nnew lines: %d\n", blank, tab, nl);
}