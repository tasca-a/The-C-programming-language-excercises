#include <ctype.h>
#include <stdio.h>
#include "utils.h"

#define MAXWORD 100

int getword(char *word, int lim);
int skipbetween(int start, int end);

int main()
{
    int c;
    char word[MAXWORD];

    while ((c = getword(word, MAXWORD)) != EOF){
        printf("word got: %s\n", word);
    }

    return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    
    if (c != EOF){
        switch (c) {
            case '"': ungetch(c); c = skipbetween('"', '"'); break;         // skip all strings
            case '\'': ungetch(c); c = skipbetween('\'', '\''); break;      // skip all chars
            case '/': c = skipbetween('/', '\n'); break;                    // skip all inline comments
            case '#': ungetch(c); c = skipbetween('#', '\n'); break;        // skip all preprocessor directives
        }
        *w++ = c;
    }

    if (!isalpha(c) && c != '_'){
        *w = '\0';
        return c;
    }

    while (--lim > 0){
        if (!isalnum(*w = getch()) && *w != '_'){
            ungetch(*w);
            break;
        }
        w++;
    }
    *w = '\0';

    return word[0];
}

/* skipbetween: skip all characters starting at start and ending at end.
                returns the first character after skipping. */
int skipbetween(int start, int end)
{
    int c;

    if ((c = getch()) != start){
        ungetch(c);
        return c;
    }

    while ((c = getch()) != end)    // skips all characters in between..
        ;

    while (isspace(c = getch()))    // skips all the spaces after the end
        ;

    return c;
}