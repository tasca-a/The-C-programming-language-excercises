#include <stdio.h>

#define SIZE 100

int strend(char *, char *);

int main()
{
    char str1[] = "Ciao come va?";
    char str2[] = "e va?";
    char str3[] = "e ua?";

    printf("s = %s\tt = %s\t%s\n", str1, str2, (strend(str1, str2)) ? "OK" : "Nope");
    printf("s = %s\tt = %s\t%s\n", str1, str3, (strend(str1, str3)) ? "OK" : "Nope");

    return 0;
}

/* strend:  returns 1 if the string t occurs at the end of the string s, and zero otherwise */
int strend(char *s, char *t)
{
    char *start_s, *start_t;
    start_s = s;
    start_t = t;

    while (*s != '\0')  // reach the end of s
        s++;

    while (*t != '\0')    // reach the end of t
        t++;

    while (--s >= start_s && --t >= start_t)
        if (*s != *t)
            return 0;

    return 1;
}