#include <stdio.h>
#include <string.h>

#define MAXLEN 1000     // max length of any input line

int mgetline(char *, int);
char *alloc(int);

/* readlines:   read input lines */
int readlines(char *lineptr[], int maxlines, char *storage, int storagesize)
{
    int len, nlines;
    char *p, line[MAXLEN];
    char *storagelimit = storage + storagesize;

    nlines = 0;
    while ((len = mgetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = storage) + (len-1) > storagelimit)   // len-1 is because '\n' is counted in len
            return -1;
        else{
            storage += len;
            line[len-1] = '\0';     // delete newline
            strcpy(p, line);
            lineptr[nlines++] = p;
        }
    
    return nlines;
}