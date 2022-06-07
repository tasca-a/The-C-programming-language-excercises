#include <stdio.h>

#define SIZE 100

void pstrcat(char *, char *);

int main()
{
    char str1[SIZE] = "ciao come "; // We make sure that there is enough space
    char str2[] = "va?";

    printf("string 1: %s\n", str1);
    printf("string 2: %s\n", str2);

    pstrcat(str1, str2);

    printf("string concat: %s\n", str1);

    return 0;
}

/* pstrcat: pointer version of the function strcat, copies the string t to the end of s. */
void pstrcat(char *s, char *t)
{
    while (*s != '\0')
        s++;
    
    while (*t != '\0')
        *s++ = *t++;

    *t = '\0';
}
