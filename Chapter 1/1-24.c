#include <stdio.h>

/* syntax checker:
check a C program for rudimentary syntax errors like unbalanced parentheses, brackets and braces. */

int main(){

    int c, p;   // p = previous character

    int parentheses, brackets, braces;
    int single_quotes, double_quotes;
    int comments;

    parentheses = brackets = braces = single_quotes = double_quotes = comments = 0;
    p = -1;

    while((c = getchar()) != EOF){
        if (c == '(') ++parentheses;
        if (c == ')') --parentheses;
        if (c == '[') ++brackets;
        if (c == ']') --brackets;
        if (c == '{') ++braces;
        if (c == '}') --braces;


        if (c == '\'' && p != '\\' && single_quotes == 0) ++single_quotes;
        else if (c == '\'' && p != '\\') --single_quotes;

        if (c == '\"' && p != '\\' && double_quotes == 0) ++double_quotes;
        else if (c == '\"' && p != '\\') --double_quotes;

        if (c == '*' && p == '/' && comments == 0) ++comments;
        else if (c == '/' && p == '*') --comments;

        p = c;
    }

    if (parentheses != 0) printf("Unbalanced parentheses!\n");
    if (brackets != 0) printf("Unbalanced brackets!\n");
    if (braces != 0) printf("Unbalanced braces!\n");
    if (single_quotes != 0) printf("Unbalanced single quotes!\n");
    if (double_quotes != 0) printf("Unbalanced double quotes!\n");
    if (comments != 0) printf("Multiline comment not closed!\n");

    return 0;
}