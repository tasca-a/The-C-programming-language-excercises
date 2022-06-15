#include <stdio.h>
#include <ctype.h>
#include "utils.h"

#define BUFSIZE 100

int getint(int *pn);

int main()
{
    int val, array[BUFSIZE];
    int n = 0;

    for (int i = 0; i < BUFSIZE; i++)
        array[i] = 0;

    while ((val = getint(&array[n++])) != EOF)
        printf("%s\n", (val != 0) ? "numero!" : "non numero");

    for (int i = 0; i < n-1; i++)
        printf("%d\n", array[i]);

    return 0;
}

/* getint:  get next integer from input into *pn */
int getint(int *pn)
{
    int c, sign;
    
    while (isspace(c = getch()))    // skip white spaces
        ;
    
    if (!isdigit(c) && c != EOF && c != '+' && c != '-'){
        //ungetch(c); // it's not number
        return 0;
    }

    sign = (c == '-') ? -1 : 1;

    if (c == '+' || c == '-'){
        c = getch();
        if (!isdigit(c)){
            ungetch(c);
            return 0;
        }
    }
    
    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10 * *pn + (c - '0');
    *pn *= sign;

    if (c != EOF)
        ungetch(c);
    
    return c;
}