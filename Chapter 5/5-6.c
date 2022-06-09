#include <stdio.h>
#include <ctype.h>

#define SIZE 100

int mgetline(char *, int);
int atoi(char *);

int main()
{
    char str1[SIZE];
    int length;

    // getline test
    length = mgetline(str1, SIZE);
    printf("Line: %sLength: %d\n", str1, length);

    // atoi test
    printf("String: %s\tNumber: %d\n", "-4586", atoi("-4586"));

    return 0;
}

/* getline: get line into s, return length */
int mgetline(char *s, int lim)
{
    int l = 0;

    while (l++ < lim && (*s = getchar()) != '\n' && *s != EOF)
        s++;
    
    *(++s) = '\0';

    return l-1;
}

/* atoi:    convert s to integer */
int atoi(char *s)
{
    int sign, out;

    sign = (*s == '-') ? -1 : 1;    // check sign

    if (*s == '-' || *s == '+')     // skip sign if found
        s++;

    for (out = 0; isdigit(*s); s++)
        out = 10 * out + (*s - '0');

    return sign * out;
}





/*
    itoa
    reverse
    strindex
    getop
*/