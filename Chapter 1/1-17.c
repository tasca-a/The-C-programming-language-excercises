#include <stdio.h>

#define MAX_LINE_LENGTH 150     /* max length of a single line */
#define CHAR_LOWER_LIMIT 80     /* all the strings longer that that will be printed */

int mygetline(char saveto[], int maxlength);

int main(){

    // Get a line with it's length
    // if is more than CHAR_LOWER, print it
    // if not, go to the next line

    char line[MAX_LINE_LENGTH];
    char len; 

    while ((len = mygetline(line, MAX_LINE_LENGTH)) > 0){
        if (len > CHAR_LOWER_LIMIT)
            printf("%s", line);

        printf("\n");
    }

    return 0;
}

/* save line and return the length */
int mygetline(char saveto[], int maxlength){
    int length = 0;
    int c;

    for (length = 0; (c = getchar()) != EOF && length < maxlength-1 && c != '\n'; ++length)
        saveto[length] = c;
    
    if (c == '\n'){
        saveto[length] = c;
        ++length;
    }

    saveto[length] = '\0';

    return length;
}