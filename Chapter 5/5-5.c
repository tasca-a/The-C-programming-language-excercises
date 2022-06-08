#include <stdio.h>

#define SIZE 100

char *mstrncpy(char *, char *, int);
char *mstrncat(char *, char *, int);
int mstrncmp(char *, char *, int);

int main()
{
    char str1[SIZE] = "Puao";

    printf("%s\n", mstrncpy(str1, "miku", 2));
    printf("%s\n", mstrncat(str1, "bauwoof", 3));
    printf("%s\n", (mstrncmp(str1, "miaobau", 5) == 0) ? "Uguale!" : "Diversa");

    return 0;
}

/* mstrncpy:    copies at most the first n characters of t in s */
char *mstrncpy(char *s, char *t, int n)
{
    char *out = s;

    for (int i = 0; *s != '\0' && *t != '\0' && i < n; i++)
        *s++ = *t++;

    return out;
}

/* mstrncat:    copies at most the first n characters of string t to the end of s */
char *mstrncat(char *s, char *t, int n)
{
    char *out = s;

    while (*s != '\0')
        s++;
    
    for (int i = 0; *t != '\0' && i < n; i++)
        *s++ = *t++;

    *s = '\0';

    return out;
}

/* mstrncmp:    compare at most n characters of string s to string t; 
                return <0 if s<t, 0 if s==t, or >0 if s>t. */
int mstrncmp(char *s, char *t, int n)
{
    for (int i = 0; *s != '\0' && *t != '\0' && i < n; s++, t++, i++)
        if (*s < *t)
            return -1;
        else if (*s > *t)
            return 1;

    return 0;
}