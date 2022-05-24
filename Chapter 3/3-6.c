#include <stdio.h>
#include <limits.h>

#define SIZE 100

void itoa(int n, char s[], int w);
void reverse(char s[]); /* taken from ex. 1-19 */

int main(){
    int test1 = 123;
    int test2 = -234;
    int test3 = INT_MAX;
    int test4 = INT_MIN;

    char mystring[SIZE];

    itoa(test1, mystring, 11);
    printf("%s\n", mystring);

    itoa(test2, mystring, 11);
    printf("%s\n", mystring);

    itoa(test3, mystring, 11);
    printf("%s\n", mystring);

    itoa(test4, mystring, 11);
    printf("%s\n", mystring);

    return 0;
}

/* itoa: convert n to characters in s */
void itoa(int n, char s[], int w){
    int i, sign;
    int flag_min = 0;
    int padding;

    if ((sign = n) < 0){  /* record sign */
        if (flag_min = (n == INT_MIN))
            n += 1;

        n = -n;         /* make n positive */
    }

    i = 0;
    do{                 /* generate digits in reverse order */
        s[i++] = n % 10 + '0';  /* get next digit */
    } while ((n /= 10) > 0);

    if (flag_min)
        s[0] += 1;

    if (sign < 0)
        s[i++] = '-';

    for (padding = w - i; padding > 0; --padding)
        s[i++] = ' ';   /* use '*' to make the padding visible */

    s[i] = '\0';

    reverse(s);
}

/* reverse: reverse the string passed in input */
void reverse(char s[]){

    // get the input size
    int size;
    for (size = 0; s[size] != '\0'; ++size);

    // create a temp array and copy the input in it
    char temp[size+1];
    for (int i = 0; (temp[i] = s[i]) != '\0'; ++i);

    // reverse the input
    for (int i = size-1; i >= 0; i--)
        s[size-1-i] = temp[i];
}