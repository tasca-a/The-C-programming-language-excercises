/*
    THIS IS NOT COMPLETE.
    I barely touched the function, but I got the point of the exercise.
*/

#include <stdio.h>
#include <stdarg.h>

void miniprintf(char *fmt, ...);

int main()
{
    printf("Miniprintf test:\n");

    miniprintf("ciao %s, oggi hai %d gatti, fatti dallo %f%% di acqua\n", "ALE", 10, 0.3f);
    
    return 0;
}

/*  miniprintf: minimal printf with variable argument list */
void miniprintf(char *fmt, ...)
{
    va_list ap;     //  points to each unnamed arg in turn
    char *p, *sval;
    int ival;
    double dval;

    va_start(ap, fmt);  // make ap point to 1st unnamed arg

    for (p = fmt; *p; p++){
        if (*p != '%'){
            putchar(*p);
            continue;
        }

        switch (*++p) {
            case 'd':
                ival = va_arg(ap, int);
                printf("%d", ival);
                break;
            case 'f':
                dval = va_arg(ap, double);
                printf("%f", dval);
                break;
            case 's':
                for (sval = va_arg(ap, char *); *sval; sval++)
                    putchar(*sval);
                break;
            case '%':
                putchar('%');
                break;
            default:
                putchar(*p);
                break;
        }
    }
    va_end(ap);  // clean up when done
}