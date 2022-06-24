#include <ctype.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXLINES 5000       /* max #lines to be sorted */
#define MAXLEN 1000 /* max length of any input line */

char *lineptr[MAXLINES];    /* pointers to text lines */

int readlines(char *lineptr[], int nlines);
int mgetline(char s[], int lim);
void writelines(char *lineptr[], int nlines);

void mqsort(void *lineptr[], int left, int right, int (*comp)(void *, void *));
int numcmp(char *, char *);

void mreverse(char **lineptr, int end);
void strlwr(char *save, char *toprocess);

int numeric = 0;    /* 1 if numeric sort */
int reverse = 0;    /* 1 if reverse sort */
int fold = 0;       /* 1 if fold upper and lower case */

/* sort input lines */
int main(int argc, char *argv[])
{
    int nlines;         /* number of input lines read */

    int c;
    while (--argc > 0 && (*(++argv)[0] == '-')){
        while ((c = *(++*argv))){
            switch (c){
                case 'n': numeric = 1; break;
                case 'r': reverse = 1; break;
                case 'f': fold = 1; break;
            }
        }
    }

    if ((nlines = readlines(lineptr, MAXLINES)) >= 0){
        /*
        if (fold)
            for (int i = 0; i < nlines; i++)
                for (int j = 0; lineptr[i][j] != '\0'; j++)
                    lineptr[i][j] = tolower(lineptr[i][j]); */

        mqsort((void **) lineptr, 0, nlines-1, (int (*)(void *, void *)) (numeric ? numcmp : strcmp));

        if (reverse)
            mreverse(lineptr, nlines);

        writelines(lineptr, nlines);
        return 0;
    } else {
        printf("Input too big to sort\n");
        return 1;
    }
}

/* mreverse:    reverse the order of pointers in lineptr */
void mreverse(char **lineptr, int end)
{
    char *tmp;

    for (int i = 0; i < end/2; i++){
        tmp = lineptr[end-(1+i)];
        lineptr[end-(1+i)] = lineptr[i];
        lineptr[i] = tmp;
    }
}


/* numcmp:  compare s1 and s2 numerically */
int numcmp(char *s1, char *s2)
{
    double v1, v2;

    v1 = atof(s1);
    v2 = atof(s2);

    if (v1 < v2)
        return -1;
    else if (v1 > v2)
        return 1;
    else
        return 0;
}

/* mqsort:  sort v[left]..v[right] into increasing order */
void mqsort(void *v[], int left, int right, int (*comp)(void *, void *))
{
    int i, last;
    char tmp1[MAXLEN];
    char tmp2[MAXLEN];
    void swap(void *v[], int, int);

    if (left >= right)  /* do nothing if array contains */
        return;         /* fewer than two elements */

    swap(v, left, (left + right)/2);
    last = left;

    for (i = left+1; i <= right; i++){
        if (fold){
            strlwr(tmp1, v[i]);
            strlwr(tmp2, v[left]);
        }
        if ((*comp)(tmp1, tmp2) < 0)
            swap(v, ++last, i); 
    }
    
    swap(v, left, last);
    mqsort(v, left, last-1, comp);
    mqsort(v, last+1, right, comp);
}

/* strlwr:  convert string to lowecase and save it in save */
void strlwr(char *save, char *toprocess)
{
    int i = 0;

    while ((save[i] = tolower(toprocess[i])) != '\0')
        i++;
}

/* readlines:   read input lines */
int readlines(char *lineptr[], int maxlines)
{
    int len, nlines;
    char *p, line[MAXLEN];

    nlines = 0;
    while ((len = mgetline(line, MAXLEN)) > 0)
        if (nlines >= maxlines || (p = malloc(len)) == NULL)
            return -1;
        else{
            line[len-1] = '\0'; /* delete newline */
            strcpy(p, line);
            lineptr[nlines++] = p;
        }

    return nlines;
}

/* mgetline: read a line into s, return length */
int mgetline(char s[], int lim){
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

/* writelines:  write output lines */
void writelines(char *lineptr[], int nlines)
{
    int i;

    for (i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

void swap(void *v[], int i, int j)
{
    void *temp;

    temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}