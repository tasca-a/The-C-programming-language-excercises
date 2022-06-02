#include <stdio.h>

#define TEST_1 "0x34AF"
#define TEST_2 "34af"

int htoi(char s[]);

int main(){

    printf("%s\t%s\n", TEST_1, TEST_2);
    printf("%d\t%d\n", htoi(TEST_1), htoi(TEST_2));

    return 0;
}

/* htoi: converts a string of hexadecimal digits into its equivalent integer value. */
int htoi(char s[]){
    int result = 0;
    int hextoint;

    for (int i = 0; (s[i] >= '0' && s[i] <= '9') || (s[i] >= 'a' && s[i] <= 'f') || (s[i] >= 'A' && s[i] <= 'F') || s[i] == 'x'; ++i){
        if (s[i] == 'x' && i != 1 && s[0] != 0)
            return -1; // Error
        
        if (s[i] >= '0' && s[i] <= '9')
            hextoint = s[i] - '0';

        if (s[i] >= 'a' && s[i] <= 'f')
            hextoint = 10 + (s[i] - 'a');

        if (s[i] >= 'A' && s[i] <= 'F')
            hextoint = 10 + (s[i] - 'A');
        
        result = 16 * result + hextoint;
    }

    return result;
}