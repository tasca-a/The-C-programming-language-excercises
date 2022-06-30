/*
    In pratica il problema sta nel fatto che a seguito di un synthax error
    tutti i successivi input producono spazzatura.
    Bisogna fare in modo che, a seguito di un synthax error, l'esecuzione
    prosegua normalmente (quindi appunto, recover from input errors)
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAXTOKEN 100

enum { NAME, PARENS, BRACKETS };

void dcl(void);
void dirdcl(void);

int gettoken(void);
int tokentype;              /* type of the last token */
char token[MAXTOKEN];       /* last token string */
char name[MAXTOKEN];        /* identifier name */
char datatype[MAXTOKEN];    /* data type = char, int, ecc. */
char out[1000];             /* output string */

/* convert declarations to words */
int main()
{
    while (gettoken() != EOF){
        strcpy(datatype, token);    /* first token on the line is the datatype */
        out[0] = '\0';

        dcl();          /* parse the rest of the line */

        if (tokentype != '\n'){
            printf("syntax error.\n");
            while (tokentype != '\n')
                gettoken();
        }
        else
            printf("%s: %s %s\n", name, out, datatype);
    }
    return 0;
}

/* dcl: parse declarator */
void dcl(void)
{
    int ns;

    ns = 0;
    while (gettoken() == '*')   /* count *'s */
        ns++;

    dirdcl();

    while (ns-- > 0)
        strcat(out, " pointer to");
}

/* dirdcl:  parse a direct declarator */
void dirdcl(void)
{
    int type;

    if (tokentype == '('){      /* ( dcl ) */
        dcl();
        if (tokentype != ')')
            printf("error: missing ).\n");
    } else if (tokentype == NAME)   /* variable name */
        strcpy(name, token);
    else
        printf("error: expected name or (dcl)\n");
    
    while ((type = gettoken()) == PARENS || type == BRACKETS)
        if (type == PARENS)
            strcat(out, " function returning");
        else {
            strcat(out, " array");
            strcat(out, token);
            strcat(out, " of");
        }
}

/* gettokens:   return next token */
int gettoken(void)
{
    int c, getch(void);
    void ungetch(int);
    char *p = token;

    while ((c = getch()) == ' ' || c == '\t')
        ;

    if (c == '(') {
        if ((c = getch()) == ')') {
            strcpy(token, "()");
            return  tokentype = PARENS;
        } else {
            ungetch(c);
            return tokentype = '(';
        }
    } else if (c == '[') {
        *p++ = c;
        while ((*p++ = getch()) != ']')
            ;
        *p = '\0';
        return tokentype = BRACKETS;
    } else if (isalpha(c)) {
        *p++ = c;
        while (isalnum(c = getch()))
            *p++ = c;
        *p = '\0';

        ungetch(c);
        return tokentype = NAME;
    } else
        return tokentype = c;
}