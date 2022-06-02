#include <stdio.h>
#include <ctype.h>

#define NUMBER '0'
#define MAXOP 100

int getop(char s[]);

int main()
{
    int type;
    char s[MAXOP];

    while ((type = getop(s)) != EOF){
        printf("%c%c", (type != NUMBER) ? type : 'N', (type != '\n') ? '\n' : '\0');
    }

    return 0;
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c;
    static char rest = -1;

    //printf("\"%c\"\n", (rest == -1) ? 'R' : rest);    // DEBUG

    while ((s[0] = c = (rest == -1) ? getchar() : rest) == ' '|| c == '\t'){    // remove preceding blanks and tabs
        if (rest != -1)
            rest = -1;
    }  

    s[1] = '\0';
    if (!isdigit(c) && c != '.')
        return c;   // not a number

    i = 0;
    if (isdigit(c))     // collect integer part
        while (isdigit(s[++i] = c = getchar()))
            ;
    if (c == '.')       // collect fraction part
        while (isdigit(s[++i] = c = getchar()))
            ;

    s[i] = '\0';

    if (c != EOF)
        rest = c;

    return NUMBER;
}