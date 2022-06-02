#include <stdio.h>
#include <stdlib.h> /* for atof() */
#include <ctype.h>
#include <math.h>

#define MAXOP   100 /* max size of operand or operator */
#define NUMBER  '0' /* signal that a number was found */
#define MAXVAL 100  /* maximum depth of val stack */
#define BUFSIZE 100
#define MAXVAR 26   /* maximum variables number */

void push(double);
double pop(void);
void printtop(void);            
void duplicatetop(void);        
void swaptopelements(void);     
void clearstack(void);          
void printallstack(void);

int getop(char []);

int getch(void);
void ungetch(int);

int sp = 0;         /* next free stack position */
double val[MAXVAL]; /* value stack */

char buf[BUFSIZE];  /* buffer for ungetch */
int bufp = 0;

double var[MAXVAR]; /* array where variables are stored */
double recent = 0;      /* most recent printed value */
char recentvar = 'A';   /* most recent variable used */

/* reverse Polish calculator */
int main(){
    int type;
    double op2;
    char s[MAXOP];

    for (int i = 0; i < MAXVAR; i++)    // clear the var array
        var[i] = 0;

    while ((type = getop(s)) != EOF){
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

/* push: push f onto value stack */
void push(double f)
{
    if (sp < MAXVAL)
        val[sp++] = f;
    else
        printf("error: stack full, can't push %g\n", f);
}

/* pop: pop and return top value from stack */
double pop(void)
{
    if (sp > 0)
        return val[--sp];
    else{
        printf("error: stack empty\n");
        return 0.0;
    }
}

/* printtop: print the top element of the stack without popping */
void printtop(void)
{
    int tmp;
    if (sp > 0){
        tmp = sp - 1;
        printf("top element of the stack: %f\n", val[tmp]);
    } else
        printf("error: stack empty\n");
}

/* duplicatetop: duplicate the top element of the stack */
void duplicatetop(void)
{
    double tmp;
    if (sp > 0){
        tmp = val[sp-1];
        val[sp++] = tmp;
    } else
        printf("error: stack empty\n");
}

/* swaptopelements: swap the two top elements of the stack */
void swaptopelements(void)
{
    double top, bottom;
    double tmp;

    if (sp > 1)
        tmp = val[sp-2], val[sp-2] = val[sp-1], val[sp-1] = tmp;
    else
        printf("error: too few elements on the stack\n");
}

/* clearstack: clear the stack */
void clearstack(void)
{
    sp = 0;
}

/* printallstack: print all the stack */
void printallstack(void)
{
    for (int i = 0; i < sp; i++)
        printf("%f ", val[i]);
    putchar('\n');
}

/* getop: get next operator or numeric operand */
int getop(char s[])
{
    int i, c, n;

    s[0] = '+';

    while ((s[1] = c = getch()) == ' ' || c == '\t')    // remove trailing blanks and tabs
        ;

    if (c == '-'){
        if (isdigit(n = getch()) || n == '.'){
            s[0] = c;
            c = n;
        }

        if (n == '\n')
            ungetch(n);
    }

    ungetch(c);

    for (i = 1; isdigit(s[i] = c = getch()) || s[i] == '.'; i++)
        ;

    s[i+1] = '\0';

    if (i == 1){
        s[0] = c, s[1] = '\0';
        return c;
    }
    else
        return NUMBER;
}

int getch(void) /* get a (possibly pushed back) character */
{
    return (bufp > 0) ? buf[--bufp] : getchar();
}

void ungetch(int c) /* push a character back on input */
{
    if (bufp >= BUFSIZE)
        printf("ungetch: too many characters\n");
    else
        buf[bufp++] = c;
}