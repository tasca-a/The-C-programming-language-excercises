#include <stdio.h>

#define SIZE 500
#define TRUE 1
#define FALSE 0

void expand(char s1[], char s2[]);
int isletterlower(int c);
int isletterupper(int c);
int isdigit(int c);

int main(){

    char test_cases[][SIZE] = {
        "a-z 0-9 A-Z",
        "ciao a-z ciao 0-9 ciao",
        "a-z0-9A-Z",
        "a-b-c",
        "-a-z-"
    };
    char out[SIZE];

    for (int i = 0; i < (sizeof(test_cases) / SIZE); ++i){
        expand(test_cases[i], out);
        printf("%s expanded: %s\n", test_cases[i], out);
    }

    return 0;
}

/* prova l'approccio coi buffer */
void expand(char s1[], char s2[]){

    /* check if the string is too short to be and expression */
    if (s1[0] == '\0' || s1[1] == '\0')
        for (int i = 0; s1[i] != '\0'; ++i)
            s2[i] = s1[i];

    int length;
    int i, j;

    /* calculate length */
    for (length = 0; s1[length] != '\0'; ++length);

    i = j = 0;
    while (i < length - 2 && s1[i+2] != '\0') {
        if (isletterlower(s1[i]) && s1[i+1] == '-' && isletterlower(s1[i+2]) && s1[i] < s1[i+2]){
            for (int z = s1[i]; z < s1[i+2]; ++z)
                s2[j++] = z;

            i += 2;
        } else
        if (isletterupper(s1[i]) && s1[i+1] == '-' && isletterupper(s1[i+2]) && s1[i] < s1[i+2]){
            for (int z = s1[i]; z < s1[i+2]; ++z)
                s2[j++] = z;
                
            i += 2;
        } else
        if (isdigit(s1[i]) && s1[i+1] == '-' && isdigit(s1[i+2]) && s1[i] < s1[i+2]){
            for (int z = s1[i]; z < s1[i+2]; ++z)
                s2[j++] = z;
                
            i += 2;
        }
        else
            s2[j++] = s1[i++];
    }

    /* fill last remaining characters */
    while (i < length) {
        s2[j++] = s1[i++];
    }

    s1[i] = s2[j] = '\0';
}

int isletterlower(int c){
    return (c >= 'a' && c <= 'z');
}

int isletterupper(int c){
    return (c >= 'A' && c <= 'Z');
}

int isdigit(int c){
    return (c >= '0' && c <= '9');
}