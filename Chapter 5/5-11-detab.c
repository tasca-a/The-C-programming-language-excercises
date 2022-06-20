#include <stdio.h>
#include <stdlib.h>

/* detab:
replaces tabs in the input with the proper number of blanks to space to the next tab stop. */

#define TAB_COLUMN 8
#define MAX_TAB_STOPS 40

#define PARAM 1
#define NO_PARAM 0

int process_arguments(int argc, char **argv);

int tab_stop_list[MAX_TAB_STOPS];

int main(int argc, char **argv){

    int tabn = process_arguments(argc, argv);

    /* DEBUG
    printf("tabn: %d\n", tabn);

    for (int i = 0; i < argc - 1; i++)
        printf("arg %d: %d\n", i+1, tab_stop_list[i]);

    printf("%s\n", (tabn == -1) ? "FAIL" : "OK");
    */

    int c;
    int col = 0;
    int ind = 0;
    int mode;

    while ((c = getchar()) != EOF){
        if (c == '\t'){

            mode = (tabn == -1 || ind >= tabn) ? NO_PARAM : PARAM;  // Check mode

            //printf("mode: %s\n", (mode == PARAM) ? "PARAM" : "NOT PARAM");

            if (mode == PARAM){
                if (col % tab_stop_list[ind] == 0){
                    for (int i = 0; i < tab_stop_list[ind]; ++i){
                        putchar(' ');
                        ++col;
                    }
                }
                else{
                    int spaces_left = (tab_stop_list[ind] - (col % tab_stop_list[ind]));

                    for (int i = 0; i < spaces_left; ++i){
                        putchar(' ');
                        ++col;
                    }
                }

                ind++;
            } else {
                if (col % TAB_COLUMN == 0){
                    for (int i = 0; i < TAB_COLUMN; ++i){
                        putchar(' ');
                        ++col;
                    }
                }
                else{
                    int spaces_left = (TAB_COLUMN - (col % TAB_COLUMN));

                    for (int i = 0; i < spaces_left; ++i){
                        putchar(' ');
                        ++col;
                    }
                }
            }
        } else{
            putchar(c);
            ++col;

            if (c == '\n'){
                col = 0;
                ind = 0;
            }
        }
    }

    return 0;
}

/* process_arguments:   process the passed arguments to create the tab stop list.
                        return the number of elements in the tab stop list, -1 if the arguments are not
                        provided correctly or not provided at all. */
int process_arguments(int argc, char **argv)
{
    int i = 0;

    // insert all arguments in the list
    while (argc-- > 1 && i < MAX_TAB_STOPS){
        if (++argv != NULL)
            tab_stop_list[i++] = atoi(*argv);
    }

    // check if the list is valid
    for (int j = 0; j < i-1; j++)
        if (tab_stop_list[j] > tab_stop_list[j+1])
            return -1;

    return (i == 0) ? -1 : i;
}