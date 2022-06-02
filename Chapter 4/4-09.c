/*
    I don't get it..
    The getch and ungetch presented in the book work as expected with an EOF.
*/

#include <stdio.h>
#include <ctype.h>

#define BUFSIZE 100

int getch(void);
void ungetch(int);

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;

/* reverse Polish calculator */
int main(){

    int c;
    
    ungetch(EOF);
    
    c = getch();

    printf("%s\n", (c == EOF) ? "ok!" : "nope..");

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