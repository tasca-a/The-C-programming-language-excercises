#include <stdio.h>

#define MAXLINE 80

int main()
{
    int c, p;       // p is the current position
    p = 0;
    while ((c = getchar()) != EOF) {
        if (p > 80){
            putchar('\n');
            p = 0;
        }

        if (c < 10)     // aka. non printable character
            printf("%x", c);
        else
            putchar(c);

        ++p;
    }
    return 0;
}