#include <stdio.h>

#define COLUMN_LENGTH 80

/* fold:
"fold" long input lines into two or more
shorter lines after the last non-blank character that occurs before the n-th
column of input. */
int main(){

    int c;
    int lwi = 0;        // lwi = last word index
    char buff[COLUMN_LENGTH+1];

    // reference
    for (int i = 0; i < 80; i++)
        putchar(' ');
    printf("<- 80 col.\n");

    for (int i = 0; (c = getchar()) != EOF; ++i){
        if (i < COLUMN_LENGTH){
            buff[i] = c;

            if (c != ' ')
                if (i == 0)
                    lwi = 0;
                else
                    if (buff[i-1] == ' ')
                        lwi = i;
            
            buff[i+1] = '\0';

        } else {
            if (c == ' '){
                buff[i] = '\0';
                printf("%s\n", buff);
                i = 0;
            } else {
                buff[i] = '\0';

                char tmp[COLUMN_LENGTH];
                int j = 0;

                for (lwi; lwi < COLUMN_LENGTH; lwi++){
                    tmp[j] = buff[lwi];
                    buff[lwi] = '\0';
                    ++j;
                }
                tmp[j] = c;

                printf("%s\n", buff);

                int z;
                for (z = 0; z <= j; z++)
                    buff[z] = tmp[z];
                buff[z] = '\0';

                lwi = 0;

                i = j;
            }
        }
    }

    printf("%s\n", buff);
    
    return 0;
}