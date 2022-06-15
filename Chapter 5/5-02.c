/*
    What type does getfloat return as its function value?
    getfloat still return an integer value, because it has to signal the coming of an EOF to the caller.
*/

#include <stdio.h>
#include <ctype.h>
#include "utils.h"

#define BUFSIZE 100

int getfloat(float *);

int main()
{
    int val;
    float array[BUFSIZE];
    int n = 0;

    for (int i = 0; i < BUFSIZE; i++)
        array[i] = 0;

    while ((val = getfloat(&array[n++])) != EOF)
        printf("%s\n", (val != 0) ? "numero!" : "non numero");

    for (int i = 0; i < n-1; i++)
        printf("%f\n", array[i]);

    return 0;
}

/* getfloat:    get next float from input into *pn */
int getfloat(float *pn)
{
    int c, sign;
    float power = 1.0;
    
    while (isspace(c = getch()))    // skip white spaces
        ;

    if (!isdigit(c) && c != EOF && c != '+' && c != '-' && c != '.')
        return 0;   // it's not number

    sign = (c == '-') ? -1 : 1;     // get the sign
    
    if (c == '+' || c == '-'){
        c = getch();
        if (!isdigit(c) && c != '.'){
            ungetch(c);
            return 0;
        }
    }

    for (*pn = 0; isdigit(c); c = getch())
        *pn = 10.0 * *pn + (c - '0'); // get the integer part

    if (c == '.'){
        c = getch();
        for (; isdigit(c); c = getch()){
            *pn = 10.0 * *pn + (c - '0');
            power *= 10.0;
        }
    }

    *pn /= power;
    *pn *= sign;

    if (c != EOF)
        ungetch(c);
    
    return c;
}