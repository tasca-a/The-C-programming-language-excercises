#include <stdio.h>
#include <ctype.h>
#include <math.h>
#include <stdlib.h> /* for atof() */
#include "utils.h"

#define SIZE 100
#define MAXVAR 26   /* maximum variables number */
#define MAXOP   100 /* max size of operand or operator */

double var[MAXVAR]; /* array where variables are stored */
double recent = 0;      /* most recent printed value */
char recentvar = 'A';   /* most recent variable used */

int getop(char s[], char in[]);

int main(int argc, char **argv)
{
    char strin[SIZE];
    int ind = 0;

    // concatenate all arguments to one string
    for (int i = 1; i < argc; i++){
        if (i != 1) strin[ind++] = ' ';
        for (int j = 0; argv[i][j] != '\0' && ind < SIZE; j++)
            strin[ind++] = argv[i][j];
    }
    strin[ind++] = '\n';
    strin[ind] = '\0';

    printf("Input: %s\n", strin);

    // feed that string to the calculator we already made
    int type;
    double op2;
    char s[MAXOP];

    while ((type = getop(s, strin)) != '\0'){
        switch (type){
            case NUMBER:
                push(atof(s));
                break;
            case '+':
                push(pop() + pop());
                break;
            case '*':
                push(pop() * pop());
                break;
            case '-':
                op2 = pop();
                push(pop() - op2);
                break;
            case '%':
                op2 = pop();
                push((int) pop() % (int) op2);
                break;
            case '/':
                op2 = pop();
                if (op2 != 0.0)
                    push(pop() / op2);
                else
                    printf("error: zero division\n");
                break;
            case 's':
                push(sin(pop()));
                break;
            case 'e':
                push(exp(pop()));
                break;
            case 'p':
                op2 = pop();
                push(pow(pop(), op2));
                break;
            case 'r':
                printf("\t%.8g\n", recent);
                break;
            case '=':
                pop(); 
                var[recentvar-'A'] = pop();
                break;
            case '\n':
                recent = pop();
                printf("\t%.8g\n", recent);
                break;
            default:
                if (s[0] >= 'A' && s[0] <= 'Z'){ // it's a variable!
                    push(var[s[0]-'A']);
                    recentvar = s[0];
                }
                else
                    printf("error: unknowkn command: \"%s\"\n", s);
                break;
        }
    }

    return 0;
}

int lastopindex = 0;
/* getop: get next operator or numeric operand */
int getop(char s[], char input[])
{
    int i, c, n;

    if (lastopindex > 0 && input[lastopindex-1] == '\0')
        return EOF;

    s[0] = '+';

    while ((s[1] = c = input[lastopindex++]) == ' ' || c == '\t')    // remove trailing blanks and tabs
        ;

    if (c == '-'){
        if (isdigit(n = input[lastopindex++]) || n == '.'){
            s[0] = c;
            c = n;
        }

        if (n == '\n')
            lastopindex--;
    }

    lastopindex--;

    for (i = 1; isdigit(s[i] = c = input[lastopindex++]) || s[i] == '.'; i++)
        ;

    s[i+1] = '\0';

    if (i == 1){
        s[0] = c, s[1] = '\0';
        return c;
    }
    else
        return NUMBER;
}