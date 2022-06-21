#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINES 1000
#define MAX_LINE_LENGTH 1000

void process_arguments(int n, char **arglist);
int get_line(char *s, int lim);
void rotate(char **array);

static int line_to_print = 10;
char *input_lines[MAX_LINES];

/* tail:    prints the last n lines of its input.
            By default, n is 10, let us say, but it can be changed by an optional argument. */
int main(int argc, char **argv)
{
    // process the input
    process_arguments(argc, argv);

    // get lines
    // TODO: refactor to extract this function
    char line[MAX_LINE_LENGTH];
    char *p;    // points to the next free location in memory
    int len, ind;

    ind = 0;
    while ((len = get_line(line, MAX_LINE_LENGTH)) > 0){
        p = malloc(len);

        strncpy(p, line, len);

        if (ind >= MAX_LINES){
            rotate(input_lines);
            ind--;
        }
        input_lines[ind++] = p;
        int lower_bound = 0;

        printf("array status:\n");
        while (lower_bound < ind)
            printf("%s - ", input_lines[lower_bound++]);
        printf("\n");
    }

    // print last line_to_print lines
    int lower_bound = (line_to_print > ind) ? 0 : ind - line_to_print;
    while (lower_bound < ind)
        printf("%s\n", input_lines[lower_bound++]);

    return 0;
}

/* process_arguments:   change number of lines to print based on the argument of the program. */
void process_arguments(int n, char **arglist)
{
    while (n-- > 1){
        if (++arglist != NULL && **arglist == '-')
            line_to_print = atoi(*arglist+1);
    }
}

/* get_line: get line into s, return length */
int get_line(char *s, int lim)
{
    int l = 0;

    // THERE'S A BUG HERE:  lower the value of MAX_LINES and reach that limit at runtime.
    //                      For some unknowkn resons, getchar() now does not return ever.
    //                      WTF.
    while (l++ < lim && (*s = getchar()) != '\n' && *s != EOF){
        //printf("l: %d\tlim: %d\t*s: %c", l, lim, (*s == EOF) ? 'E' : (*s == '\n') ? 'N' : *s);
        s++;
    }

    *(++s) = '\0';

    return l-1;
}

/* rotate:  rotate array to the left by one. The first element is lost */
void rotate(char **array)
{
    while (++*array != NULL){
        *(array-1) = *array;
    }
}