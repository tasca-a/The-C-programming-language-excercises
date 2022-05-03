#include <stdio.h>

/* detab:
replaces tabs in the input with the proper number of blanks to space to the next tab stop. 

Assume a fixed set of tab stops, say every n columns. Should n be a variable or a symbolic parameter?
n should be a symbolic parameter. */

#define TAB_COLUMN 4

int main(){

    int c;
    int col = 0;

    while ((c = getchar()) != EOF){
        if (c == '\t'){
            if (col % TAB_COLUMN == 0){
                for (int i = 0; i < TAB_COLUMN; ++i){
                    putchar(' ');
                    ++col;
                }
            }
            else{
                int spaces_left = (TAB_COLUMN - (col % TAB_COLUMN));

                for (int i = 0; i < spaces_left; ++i){
                    putchar(' ');
                    ++col;
                }
            }
        } else{
            putchar(c);
            ++col;

            if (c == '\n')
                col = 0;
        }
    }

    return 0;
}