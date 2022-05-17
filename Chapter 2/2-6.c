#include <stdio.h>

unsigned setbits(unsigned x, int p, int n, unsigned y);
void printBinary(unsigned value);

int main(){
    unsigned ptrn1 = 0b10110111;
    unsigned ptrn2 = 0b10100010;

    printf("pattern 1: "); printBinary(ptrn1);
    printf("pattern 2: "); printBinary(ptrn2);
    printf("\noutput: "); printBinary(setbits(ptrn1, 3, 2, ptrn2));

    return 0;
}

/* setbits: returns x with the n bits that begin at position p set to the rightmost n bits of y, 
            leaving the other bits unchanged */
unsigned setbits(unsigned x, int p, int n, unsigned y){
    unsigned base = ~(~0<<n);
    unsigned mask1 = ~(base<<(p-n+1))&x;
    unsigned mask2 = (base&y)<<(p-n+1);

    return mask1 | mask2;
}

void printBinary(unsigned value){
    for (unsigned count = 0b1 << (sizeof(value)*8-1); count > 0; count = count >> 1)
        if (value & count)
            putchar('1'); //printf("1");
        else
            putchar('0'); //printf("0");
    putchar('\n');
}