#include <stdio.h>
#include <limits.h>
#include <float.h>

#define LINE_LENGTH 80

void from_headers(void);
void from_computation(void);

/* ranges:
Determine the ranges of char, short, int, and long variables, both signed and unsigned, by printing appropriate
values from standard headers and by direct computation */
int main(){

    from_headers();
    for (int i = 0; i < LINE_LENGTH; ++i) putchar('='); putchar('\n');
    from_computation();

    return 0;
}

void from_headers(){
    printf("From header:\n\n");

    printf("char =\tlower: %u\t\t\tupper: %u\t\t\tunsigned\n",  0,  UCHAR_MAX);
    printf("char =\tlower: %d\t\t\tupper: %d\t\t\tsigned\n",    CHAR_MIN,   CHAR_MAX);
    printf("short =\tlower: %u\t\t\tupper: %u\t\t\tunsigned\n", 0,  USHRT_MAX);
    printf("short =\tlower: %d\t\t\tupper: %d\t\t\tsigned\n",   SHRT_MIN,   SHRT_MAX);
    printf("int =\tlower: %u\t\t\tupper: %u\t\tunsigned\n",   0,   UINT_MAX);
    printf("int =\tlower: %d\t\tupper: %d\t\tsigned\n",     INT_MIN,    INT_MAX);
    printf("long =\tlower: %lu\t\t\tupper: %lu\tunsigned\n",  0,  ULONG_MAX);
    printf("long =\tlower: %ld\tupper: %ld\tsigned\n",  LONG_MIN,   LONG_MAX);
}

void from_computation(){
    printf("From computation:\n\n");

    /* for unsigned types it is sufficient to underflow them assigning -1 */
    unsigned char uchar_max = -1;
    unsigned short ushrt_max = -1;
    unsigned int uint_max = -1;
    unsigned long ulong_max = -1;

    /* for signed types it must be found the underflow and overflow point */
    char char_l, char_u;
    short shrt_l, shrt_u;
    int int_l, int_u;
    long long_l, long_u;

    char c; for (c = uchar_max / 2; c >= 0; ++c) char_u = c; char_l = c; printf("char\tOK\n");
    short s;for (s = ushrt_max / 2; s >= 0; ++s) shrt_u = s; shrt_l = s; printf("short\tOK\n");
    int i;  for (i = uint_max / 2; i >= 0; ++i) int_u = i; int_l = i;   printf("int\tOK\n");
    long l; for (l = ulong_max / 2; l >= 0; ++l) long_u = l; long_l = l; printf("long\tOK\n\n");

    printf("char =\tlower: %u\t\t\tupper: %u\t\t\tunsigned\n",  0,  uchar_max);
    printf("char =\tlower: %d\t\t\tupper: %d\t\t\tsigned\n",    char_l,   char_u);
    printf("short =\tlower: %u\t\t\tupper: %u\t\t\tunsigned\n", 0,  ushrt_max);
    printf("short =\tlower: %d\t\t\tupper: %d\t\t\tsigned\n",   shrt_l,   shrt_u);
    printf("int =\tlower: %u\t\t\tupper: %u\t\tunsigned\n",   0,   uint_max);
    printf("int =\tlower: %d\t\tupper: %d\t\tsigned\n",     int_l,    int_u);
    printf("long =\tlower: %lu\t\t\tupper: %lu\tunsigned\n",  0,  ulong_max);
    printf("long =\tlower: %ld\tupper: %ld\tunsigned\n",  long_l,   long_u);
}