#include <stdio.h>

#define MAXLINE 20     /* maximum input line size */

int mygetline(char line[], int maxline);
void copy(char to[], char from[]);

/* print logest input line */
int main(){
    int len;            /* current line length */
    int max;            /* maximum length seen so far */
    char line[MAXLINE];     /* current input line */
    char longest[MAXLINE];  /* longest line saved here */

    max = 0;
    while((len = mygetline(line, MAXLINE)) > 0)
        if (len > max){
            max = len;
            copy(longest, line);
        }

    if (max > 0)        /* there was a line */
        printf("\n%s\nlenght: %d\n", longest, max);

    return 0;
}

/* mygetline: read a line into s, return length */
int mygetline(char s[], int lim){
    int c, i;

    for (i = 0; (c = getchar()) != EOF && c != '\n'; ++i)
        if (i < lim-1)
            s[i] = c;
        else if (i == lim-1)
            s[i] = '\0';

    if (c == '\n' && i < lim-1) {
        s[i] = c;
        ++i;
        s[i+1] = '\0';
    }

    return i;
}

/* copy: copu 'from' omtp 'to'; assume to is big enough */
void copy(char to[], char from[]){
    int i;

    i = 0;
    while ((to[i] = from[i]) != '\0')
        ++i;
}