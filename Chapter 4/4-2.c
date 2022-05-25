#include <stdio.h>
#include <ctype.h>

#define TRUE 1
#define FALSE 0

double atof(char s[]);
/*
int isspace(char c);
int isdigit(char c);
*/

int main(){

    printf("%s is %f\n", "123.56", atof("123.56"));
    printf("%s is %f\n", "-123.56", atof("-123.56"));
    printf("%s is %f\n", "-123.56e-4", atof("-123.56e-4"));
    printf("%s is %f\n", "-123.56e4", atof("-123.56e4"));


    return 0;
}

/* atof: convert string s to double */
double atof(char s[]){
    double val, power, expval;
    int i, sign, expsign;

    for (i = 0; isspace(s[i]); i++) /* skip white space */
        ;

    sign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (val = 0.0; isdigit(s[i]); i++)
        val = 10.0 * val + (s[i] - '0');

    if (s[i] == '.')
        i++;

    for (power = 1.0; isdigit(s[i]); i++){
        val = 10.0 * val + (s[i] - '0');
        power *= 10.0;
    }

    if  (s[i] == 'e' || s[i] == 'E')
        i++;

    expsign = (s[i] == '-') ? -1 : 1;
    if (s[i] == '+' || s[i] == '-')
        i++;

    for (expval = 0; isdigit(s[i]); i++)
        expval = 10 * expval + (s[i] - '0');

    for (expval; expval > 0; expval--)
        if (expsign > 0)
            power /= 10;
        else
            power *= 10;


    return sign * val / power;
}

/*
int isspace(char c){
    return (c == ' ') ? TRUE : FALSE;
}

int isdigit(char c){
    return (c >= '0' && c <= '9') ? TRUE : FALSE;
}
*/