#include <stdio.h>

unsigned invert(unsigned x, int p, int n);
void printBinary(unsigned value, int length);

int main(){
    unsigned ptrn = 0b11110111;

    printf("input:\t"); printBinary(ptrn, 8);
    printf("output:\t"); printBinary(invert(ptrn, 4, 3), 8);

    return 0;
}

unsigned invert(unsigned x, int p, int n){
    return (~(~0<<n)<<(p-n+1))^x;
}

void printBinary(unsigned value, int length){
    for (unsigned count = 0b1 << (length-1); count > 0; count = count >> 1)
        if (value & count)
            putchar('1'); //printf("1");
        else
            putchar('0'); //printf("0");
    putchar('\n');
}