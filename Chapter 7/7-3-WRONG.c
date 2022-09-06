/*
    THIS IS NOT COMPLETE.
    I barely touched the function, but I got the point of the exercise.
    
    I attempted to make flags, width and precision work but I probably used
    the wrong approach because apparently custom strings can't be used as the
    formatter string for printf.
*/

#include <stdio.h>
#include <stdarg.h>

#define STRLEN 150
#define TRUE 1
#define FALSE 0

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

    char faw[STRLEN];   // flags and width: group together all printf modifiers
    char *faw_p;
    char format[STRLEN];
    int stop;

    for (p = fmt; *p; p++){
        if (*p != '%'){
            putchar(*p);
            continue;
        }

        faw_p = faw;    // set the pointer to the start of the string
        stop = FALSE;

        faw[0] = '\0';  // clear the faw string
        
        while (!stop){
            switch (*++p) {
                
                // Flags
                case '#': case '0': case '-': 
                case ' ': case '+': 
                    *faw_p++ = *p;
                    *faw_p = '\0';
                    break;

                // Width and precision
                case 1: case 2: case 3: case 4:
                case 5: case 6: case 7: case 8:
                case 9: case '.':
                    *faw_p++ = *p;
                    *faw_p = '\0';
                    break;

                // Conversion specifiers
                case 'd':
                    ival = va_arg(ap, int);
                    //printf("\n\ndebug: format = -%s-\n\n", format);
                    sprintf(format, "%s%%d", faw);
                    printf(format, ival);
                    stop = TRUE;
                    break;
                case 'f':
                    dval = va_arg(ap, double);
                    sprintf(format, "%s%%f", faw);
                    printf("%f", dval);
                    stop = TRUE;
                    break;
                case 's':
                    for (sval = va_arg(ap, char *); *sval; sval++)
                        putchar(*sval);
                    stop = TRUE;
                    break;
                case '%':
                    putchar('%');
                    stop = TRUE;
                    break;
                default:
                    putchar(*p);
                    stop = TRUE;
                    break;
            }
        }
    }
    va_end(ap);  // clean up when done
}