#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"

#define SIZE 100

int mgetline(char *s, int lim);
int atoi(char *s);
char *itoa(int n, char *s);
void reverse(char *s);
int strindex(char *s, char *t);
int getop(char *s);

int main()
{
    char str1[SIZE];
    int length;
    int op;

    // getline test
    length = mgetline(str1, SIZE);
    printf("Line: %sLength: %d\n", str1, length);

    // atoi test
    printf("String: %s\tNumber: %d\n", "-4586", atoi("-4586"));

    // itoa test
    printf("Number: %d\tString: %s\n", -234, itoa(-234, str1));

    // strindex test
    printf("String: %s\tOther: %s\tStrindex: %d\n", "quaqquew", "uew", strindex("quaqquew", "uew"));

    // getop test
    while ((op = getop(str1)) != EOF){
        printf("Operator: %c\tString: %s\n", (op == NUMBER) ? 'N' : op, str1);
    }

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

/* strindex:    return index of t in s, -1 if none */
int strindex(char *s, char *t)
{
    int ls, lt;
    int i, l;

    // get lengths
    for (ls = 0; *s++ != '\0'; ls++)
        ;
    for (lt = 0; *t++ != '\0'; lt++)
        ;

    // restore pointers
    s -= ls + 1;
    t -= lt + 1;
    
    for (i = 0; i <= (ls - lt); i++, s++){
        for (l = 0; *s == *t && *t != '\0'; l++){
            t++;
            s++;
        }

        if (*t == '\0')
            return i;
        else{
            t -= l;
            s -= l;
        }
    }

    return -1;
}

/* getop:   get next operator or numeric operand */
int getop(char *s)
{
    int c, n;

    while (isspace(c = getch())) // remove heading spaces
        ;

    if (c == '+' || c == '-'){ // check if + and - are operator or part of a number
        if (!isdigit(n = getch()) && n != '.')
            return c;
        else
            ungetch(n);
    } else {
        if (!isdigit(c) && c != '.')
            return c;
        else
            ungetch(c);
    }

    if (c == '+' || c == '-')
        *s++ = c;

    while (isdigit(*s++ = getch())) // get integer part
        ;
    s -= 1;

    if (*s++ == '.'){
        while (isdigit(*s++ = getch())) // get fractional part
            ;
        s -= 1;
    }

    *s = '\0';
    
    return NUMBER;
}