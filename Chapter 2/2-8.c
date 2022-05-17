#include <stdio.h>

void printBinary(unsigned value);
unsigned rightrot(unsigned x, int n);

int main(){
    unsigned ptrn = 0b11011011;

    printf("input:\t"); printBinary(ptrn);
    printf("output:\t"); printBinary(rightrot(ptrn, 3));

    return 0;
}

unsigned rightrot(unsigned x, int n){
    return ((~(~0<<n)&x)<<(sizeof(x)*8-n))|(x>>n);
}

void printBinary(unsigned value){
    for (unsigned count = 0b1 << (sizeof(value)*8-1); count > 0; count = count >> 1)
        if (value & count)
            putchar('1'); //printf("1");
        else
            putchar('0'); //printf("0");
    putchar('\n');
}