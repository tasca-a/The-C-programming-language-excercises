#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define SIZE 100

int mgetline(char *, int);
int atoi(char *);
char *itoa(int, char *);
void reverse(char *s);

int main()
{
    char str1[SIZE];
    int length;

    // getline test
    length = mgetline(str1, SIZE);
    printf("Line: %sLength: %d\n", str1, length);

    // atoi test
    printf("String: %s\tNumber: %d\n", "-4586", atoi("-4586"));

    // itoa test
    printf("Number: %d\tString: %s\n", -234, itoa(-234, str1));

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

/* itoa:    convert n to characters in s */
char *itoa(int n, char *s)
{
    int sign;
    char *start = s;

    if ((sign = n) < 0)
        n = -n;

    do {
        *s++ = n % 10 + '0';
    } while ((n /= 10) > 0);

    if (sign < 0)
        *s++ = '-';
    
    *s = '\0';
    
    reverse(start);

    return start;
}

/* reverse: reverse the string passed in input */
void reverse(char *s)
{
    char *start, *end;
    char tmp;

    for (end = start = s; *end != '\0'; end++)
        ;
    
    for (end -= 1; start < end; start++, end--)
        tmp = *start, *start = *end, *end = tmp;
}

/*
    strindex
    getop
*/