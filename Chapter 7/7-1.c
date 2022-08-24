/*
    Converts upper case to lower or lower case to upper, 
    depending on the name it is invoked with, as found in argv [0]
*/

#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define UPPER 1
#define LOWER 0

static int MODE;

int main(int argc, char **argv)
{    
    if (strcmp(*argv, "./upper") == 0)
        MODE = UPPER;
    else if (strcmp(*argv, "./lower") == 0)
        MODE = LOWER;
    else
        return 1;

    int c;
    while ((c = getchar()) != EOF)
        switch (MODE) {
            case UPPER: putchar(toupper(c)); break;
            case LOWER: putchar(tolower(c)); break;
        }
    
    return 0;
}