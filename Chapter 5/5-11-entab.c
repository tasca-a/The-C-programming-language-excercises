#include <stdio.h>
#include <stdlib.h>

/* entab:
replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing. */

#define TAB_COLUMN 8
#define MAX_TAB_STOPS 40

int process_arguments(int argc, char **argv);

int tab_stop_list[MAX_TAB_STOPS];

int main(int argc, char **argv)
{
    int tabn = process_arguments(argc, argv);

    /* DEBUG
    printf("tabn: %d\n", tabn);

    for (int i = 0; i < argc - 1; i++)
        printf("arg %d: %d\n", i+1, tab_stop_list[i]);

    printf("%s\n", (tabn == -1) ? "FAIL" : "OK");
    */

    int c;
    int col = 0;

    while ((c = getchar()) != EOF){
        if (c == '\t'){
            if (col % TAB_COLUMN == 0)
                for (int i = 0; i < TAB_COLUMN; ++i)
                    ++col;
            else{
                int spaces_left = (TAB_COLUMN - (col % TAB_COLUMN));

                for (int i = 0; i < spaces_left; ++i)
                    ++col;
            }
        }else
            if (c != '\n')
                ++col;


        if (c == '\n'){
            printf("columns: %d\n", col);

            int tabs, spaces;
            
            if (tabn == -1){
                tabs = col / TAB_COLUMN;
                spaces = col % TAB_COLUMN;
            } else {
                int colcount;

                for (tabs = 0, colcount = 0; col > (tab_stop_list[tabs] - colcount) && tabs < tabn; tabs++){
                    col -= tab_stop_list[tabs] - colcount;
                    colcount = tab_stop_list[tabs];
                }

                tabs += col / TAB_COLUMN;
                spaces = (col < TAB_COLUMN) ? col : col % TAB_COLUMN;     
            }

            for (int i = 0; i < tabs; i++)
                putchar('\t');

            for (int i = 0; i < spaces; i++)
                putchar(' ');

            printf("<-\n");

            col = 0;
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