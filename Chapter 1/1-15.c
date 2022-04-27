#include <stdio.h>

int fahr_to_celsius(int fahr);

int main(){

    int fahr;
    int lower, upper, step;

    lower = 0;
    upper = 300;
    step = 20;

    fahr = lower;
    while (fahr <= upper){
        printf("%d\t%d\n", fahr, fahr_to_celsius(fahr));
        fahr = fahr + step;
    }

    return 0;
}

/* return the integer conversion from fahrenheit to celsius */
int fahr_to_celsius(int fahr){
    return 5 * (fahr - 32) / 9;
}