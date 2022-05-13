#include <stdio.h>

#define TRUE 1
#define FALSE 0

void squeeze(char s1[], char s2[]);

int main(){
    char string1[] = "ciao questo è un test di prova";
    char string2[] = "cio";

    squeeze(string1, string2);

    printf("%s\n", string1);

    return 0;
}

/* squeeze: deletes each character in s1 that matches any character in the string s2 */
void squeeze(char s1[], char s2[]){
    int i, j;
    int present;

    for (i = j = 0; s1[i] != '\0'; ++i){

        present = FALSE;

        for (int z = 0; s2[z] != '\0'; ++z)
            if (s1[i] == s2[z])
                present = TRUE;
        
        if (!present)
            s1[j++] = s1[i];
    }

    s1[j] = '\0';
}