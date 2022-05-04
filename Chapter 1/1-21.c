#include <stdio.h>

/* entab:
replaces strings of blanks by the minimum number of tabs and blanks to achieve the same spacing.

When either a tab or a single blank would suffice to reach a tab stop, which should be given preference?
The tab, because with a single character it cover one or more spaces instead of the single black which covers only one space. */

#define TAB_COLUMN 4

int main(){

    // finchè non raggiungi EOF
    // conta quante colonne ci sono al prossimo \n
    // cicla e metti tutti i tab possibili e, quando non puoi più, metti gli spazi rimamenti

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

            int tabs = col / TAB_COLUMN;
            int spaces = col % TAB_COLUMN;

            printf("tabs: %d\t spaces: %d\n", tabs, spaces);

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