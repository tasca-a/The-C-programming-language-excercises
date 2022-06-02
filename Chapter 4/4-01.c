#include <stdio.h>
#include <string.h>

int strrindex(char s[], char t[]);

int main(){

    char test[] = "hello this is a string";
    char ptrn1[] = "str";
    char ptrn2[] = "qua";

    printf("%s\n", test);
    printf("pattern: %s\trightmost position: %d\texpected: %d\n", ptrn1, strrindex(test, ptrn1), 16);
    printf("pattern: %s\trightmost position: %d\texpected: %d\n", ptrn2, strrindex(test, ptrn2), -1);

    return 0;
}

int strrindex(char s[], char t[]){
    int i;
    
    for (i = strlen(s) - strlen(t); i >= 0; i--)
        if (s[i] == t[0] && s[i+1] == t[1] && s[i+2] == t[2])
            return i;

    return -1;
}