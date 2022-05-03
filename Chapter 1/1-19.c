#include <stdio.h>

#define LINE_LENGTH 80

void reverse(char s[]);

int main(){

    int c, cursor = 0;
    char line[LINE_LENGTH];

    while ((c = getchar()) != EOF){
        if (c != '\n' && cursor < LINE_LENGTH-1){
            line[cursor] = c;
            ++cursor;
        } else {
            line[cursor] = '\0';
            cursor = 0;

            reverse(line);

            printf("%s\n", line);
        }
    }

    return 0;
}

/* reverse: reverse the string passed in input */
void reverse(char s[]){

    // get the input size
    int size;
    for (size = 0; s[size] != '\0'; ++size);

    // create a temp array and copy the input in it
    char temp[size+1];
    for (int i = 0; (temp[i] = s[i]) != '\0'; ++i);

    // reverse the input
    for (int i = size-1; i >= 0; i--)
        s[size-1-i] = temp[i];
}