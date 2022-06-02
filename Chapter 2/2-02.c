#include <stdio.h>

#define TRUE 1
#define FALSE 0

#define LIM 80

int main(){

    int condition = TRUE;
    char s[LIM];
    int c;

    int i = 0;
    while (condition){
        if (i < LIM-1)
            if ((c = getchar()) != '\n')
                if (c != EOF){
                    s[i] = c;
                    ++i;
                } else
                    condition = FALSE;
            else
                condition = FALSE;
        else
            condition = FALSE;
    }

    return 0;
}