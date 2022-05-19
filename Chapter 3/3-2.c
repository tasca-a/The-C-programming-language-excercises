#include <stdio.h>

#define SIZE 80

void escape(char[], char[]);
void escape_reverse(char[], char[]);

int main(){

    char str1[SIZE] = "This is\ta\tstring.\nNew line.";
    char res1[SIZE*2];

    escape(str1, res1);
    printf("Escape\nInput: %s\nOutput: %s\n\n", str1, res1);

    escape_reverse(res1, str1);
    printf("Escape_revese\nInput: %s\nOutput: %s\n", res1, str1);

    return 0;
}

/* escape:  converts characters like newline and tab into visible escape sequences like \n and \t as it copies the
            string t to s. */
void escape(char s[], char t[]){
    int j = 0;
    for (int i = 0; s[i] != '\0'; ++i){
        switch (s[i]){
            case '\n': t[j++] = '\\'; t[j] = 'n'; break;
            case '\t': t[j++] = '\\'; t[j] = 't'; break;

            /* you can continue to add here other escape sequences */

            default: t[j] = s[i]; break;
        }

        ++j;
    }
}

/* escape_reverse: the exact reverse of the escape function. */
void escape_reverse(char t[], char s[]){
    int j = 0;
    for (int i = 0; t[i] != '\0'; ++i){
        switch (t[i]){
            case '\\': switch (t[++i]){
                case 'n': s[j] = '\n'; break;
                case 't': s[j] = '\t'; break;

                /* you can continue to add here other escape sequences */

                case '0': return; break;
                default: s[j] = '\\'; break;
            }; break;

            default: s[j] = t[i]; break;
        }
        j++;
    }
}