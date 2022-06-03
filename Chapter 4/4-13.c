#include <stdio.h>

void reverse(char []);

int main()
{
    char s[] = "String to be reversed";

    reverse(s);

    printf("%s\n", s);

    return 0;
}

/* reverse: reverses the string s in place recursively. */
void reverse(char s[])
{
    static int pos = -1;
    static int i = 0;

    int c = s[++pos];

    if (c == '\0')
        return;
    else
        reverse(s);
    
    s[i++] = c;
    s[i] = '\0';

    if (pos == 0)
        i = 0;

    pos--;
}
