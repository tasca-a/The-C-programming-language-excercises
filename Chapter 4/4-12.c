#include <stdio.h>

#define SIZE 100

void ritoa(int, char []);

int main()
{
    char s[SIZE];

    ritoa(123, s), printf("%s\n", s);
    ritoa(-3456, s), printf("%s\n", s);
    ritoa(-5, s), printf("%s\n", s);

    return 0;
}

/* ritoa:   converto an integer into a string by calling itself recursively. */
void ritoa(int n, char s[])
{
    static int i = 0;
    static int calls = 0;   // keep track the number of calls.

    calls++;

    if (n < 0){
        s[i++] = '-';
        n = -n;
    }

    if (n / 10 > 0)
        ritoa(n/10, s);
    
    s[i++] = (n % 10) + '0';
    s[i] = '\0';

    if (calls == 1) // if we are in the first call, reset the index for future function calls.
        i = 0;

    calls--;
}