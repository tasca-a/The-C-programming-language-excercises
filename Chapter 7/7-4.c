#include <stdio.h>
#include <stdarg.h>

void miniscanf(char *fmt, ...);

int main()
{
    int a, b;
    char str[1000];

    printf("Scanf test:\n");
    
    scanf("%d %s %d", &a, str, &b);

    printf("Scanf result: %d\t-%s\t-%d\n", a, str, b);

    miniscanf("%d %s %d", &a, str, &b);

    printf("Miniscanf result: %d\t-%s\t-%d\n", a, str, b);

    return 0;
}

/*  miniscanf: minimal scanf with variable argument list */
void miniscanf(char *fmt, ...)
{
    va_list ap;     //  points to each unnamed arg in turn
    char *p, *sval;

    va_start(ap, fmt);  // make ap point to 1st unnamed arg

    for (p = fmt; *p; p++){
        if (*p != '%'){
            putchar(*p);
            continue;
        }

        switch (*++p) {
            case 'd':
                scanf("%d", va_arg(ap, int*));
                break;
            case 'f':
                scanf("%f", va_arg(ap, float*));
                break;
            case 's':
                scanf("%s", va_arg(ap, char*));
                break;
            case '%':
                scanf("%%", va_arg(ap, char*));
                break;
            default:
                break;
        }
    }
    va_end(ap);  // clean up when done
}