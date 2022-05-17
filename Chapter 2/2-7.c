#include <stdio.h>

unsigned invert(unsigned x, int p, int n);
void printBinary(unsigned value);

int main(){
    unsigned ptrn = 0b11110111;

    printf("input:\t"); printBinary(ptrn);
    printf("output:\t"); printBinary(invert(ptrn, 4, 3));

    return 0;
}

/* invert: returns x with the n bits that begin at position p inverted */
unsigned invert(unsigned x, int p, int n){
    return (~(~0<<n)<<(p-n+1))^x;
}

void printBinary(unsigned value){
    for (unsigned count = 0b1 << (sizeof(value)*8-1); count > 0; count = count >> 1)
        if (value & count)
            putchar('1'); //printf("1");
        else
            putchar('0'); //printf("0");
    putchar('\n');
}