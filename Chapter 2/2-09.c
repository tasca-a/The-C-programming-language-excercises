#include <stdio.h>

/*  In a two's complement number system, x &= (x-1) deletes the rightmost l-bit in x. Explain why.
    Because (x-1) is the inverse of x starting from the rightmost 1 bit, so if you & x and (x-1) you set to 0
    all the bits after the rightmost 1 in x. */

int bitcount(unsigned x);
void printbinary(unsigned value);

int main(){

    unsigned ptrn = 0b11000101;

    printf("input = "); printbinary(ptrn);
    printf("bit counted: %d\n", bitcount(ptrn));

    return 0;
}

/* bitcount: count 1 bits in x*/
int bitcount(unsigned x){
    int b;
    
    while (x){
        x &= (x-1);
        ++b;
    }

    return b;
}

void printbinary(unsigned value){
    for (unsigned count = 0b1 << (sizeof(value)*8-1); count > 0; count = count >> 1)
        if (value & count)
            putchar('1'); //printf("1");
        else
            putchar('0'); //printf("0");
    putchar('\n');
}