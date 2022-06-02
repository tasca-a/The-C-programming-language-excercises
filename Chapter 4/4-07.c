/*
    Should ungets know about buf and bufp, or should it just use ungetch?
    No it should not know anything about buf and bufp: reusing already implemented functions
    is a good design practice and ensures that everything keeps working as expected.
*/

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);
void ungets(char []);

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;

/* reverse Polish calculator */
int main(){
    
    /* ungets tests */
    char string[] = "this is a test string";
    ungets(string);

    int c;
    while ((c = getch()) != EOF)
        printf("%c\n", (char) c);

    return 0;
}

/* getch: get a (possibly pushed back) character */
int getch(void)
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

/* ungetch: push a character back on input */
void ungetch(int c)
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}

/* ungets: push back an entire string onto the input */
void ungets(char s[])
{
    int l;

    for (l = 0; s[l] != '\0'; l++)  // get the string length
        ;
    
    for (l -= 1; l >= 0; l--)   // push back all characters in reverse
        ungetch(s[l]);
}