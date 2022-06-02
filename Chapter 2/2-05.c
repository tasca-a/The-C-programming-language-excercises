#include <stdio.h>

#define TRUE 1
#define FALSE 0

int any(char s1[], char s2[]);

int main(){

    char string1[] = "Prima stringa di test";
    char string2[] = "qzmzq";
    char string3[] = "xqx";

    printf("Input: %s\t%s\nFirst location: %d\nExpected:%d\n", string1, string2, any(string1, string2), 3);
    printf("Input: %s\t%s\nFirst location: %d\nExpected:%d\n", string1, string3, any(string1, string3), -1);

    return 0;
}

/* any: returns the first location in the string s1 where any character from the string s2 occurs, 
        or -1 if s1 contains no characters from s2 */
int any(char s1[], char s2[]){
    int i;
    int present = FALSE;

    for (i = 0; s1[i] != '\0' && !present; ++i)
        for (int j = 0; s2[j] != '\0'; ++j)
            if (s1[i] == s2[j]){
                present = TRUE;
                return i;
            }

    return -1;
}
