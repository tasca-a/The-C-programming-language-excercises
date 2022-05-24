#include <stdio.h>

#define SIZE 100

void itob(int n, char s[], int b);
void reverse(char s[]);

int main(){
    int test1 = -1234;
    int test2 = 65535;
    int test3 = -4095;
    int test4 = 0;

    char mystring[SIZE];

    itob(test1, mystring, 16);
    printf("dec = %d\t%s = %s\texpected = %s\n", test1, "hex", mystring, "-4d2");

    itob(test2, mystring, 16);
    printf("dec = %d\t%s = %s\texpected = %s\n", test2, "hex", mystring, "ffff");

    itob(test3, mystring, 8);
    printf("dec = %d\t%s = %s\texpected = %s\n", test3, "oct", mystring, "-7777");

    itob(test4, mystring, 16);
    printf("dec = %d\t\t%s = %s\t\texpected = %s\n", test4, "oct", mystring, "0");

    return 0;
}

/* itob: converts the integer n into a base b character representation in the string s */
void itob(int n, char s[], int b){
    // If b > 26, we don't have enough letters in the alphabet.
    if (b > 26){
        s[0] = 'E', s[1] = '\0';
        return;
    }

    int i, sign;
    int remainder;

    if ((sign = n) < 0)
        n = -n;

    i = 0;
    do{
        remainder = n % b;

        if (remainder >= 10)
            s[i++] = (remainder - 10) + 'A';
        else
            s[i++] = remainder + '0';

    } while ((n /= b) > 0);

    if (sign < 0)
        s[i++] = '-';

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