#include <stdio.h>
#include <stdbool.h>

/* comment remover:
remove all comments from a C program. */

int main(){

    int c, p;
    bool inl, ml;

    p = -1;
    inl = ml = false;

    while((c = getchar()) != EOF){
        if (p != -1){
            if (c != '/' && c != '*' && inl == false && ml == false){
                if (p == '/' || p == '*')
                    putchar('/');
                
                putchar(c);
            }
            else
            if (p == '/' && c == '/' && inl == false && ml == false)
                inl = true;
            else
            if (p == '/' && c == '*' && inl == false && ml == false)
                ml = true;
            else
            if (p == '*' && c == '/' && inl == false && ml == true){
                ml = false;
                putchar('\n');
                c = '\n';
            }
            else
            if (c == '\n' && inl == true){
                inl = false;
                putchar('\n');
            }
        } else
        if (c != '/')
            putchar(c);

        p = c;
    }

    return 0;
}