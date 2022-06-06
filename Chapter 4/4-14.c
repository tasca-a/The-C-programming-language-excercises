#include <stdio.h>

#define swap(t, x, y) {t tmp = x; x = y; y = tmp;}

int main()
{
    int a, b;
    char c, d;

    a = 1;
    b = 2;

    printf("a = %d\tb = %d\n", a, b);
    swap(int, a, b);
    printf("a = %d\tb = %d\n", a, b);

    c = 'X';
    d = 'Y';

    printf("c = %c\td = %c\n", c, d);
    swap(char, c, d);
    printf("c = %c\td = %c\n", c, d);

    return 0;
}