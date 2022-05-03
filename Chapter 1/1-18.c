#include <stdio.h>

#define LINE_LENGTH 100

void mygetline(char save[], int limit);
void removestuff(char line[]);

int main(){
    char line[LINE_LENGTH];

    mygetline(line, LINE_LENGTH);
    removestuff(line);
    
    printf("%s\n", line);
}

void mygetline(char save[], int limit){
    int i;
    for (i = 0; i < limit-1 && (save[i] = getchar()) != '\n'; i++);
    save[i] = '\0';
}

void removestuff(char line[]){
    int j = 0;
    for (int i = 0; line[i] != '\0'; i++){
        if ((line[i] != ' ' && line[i] != '\t') || (line[i] == ' ' && line[i+1] != ' ') || (line[i] == '\t' && line[i+1] != '\t')){
            line[j] = line[i];
            ++j;
        }
    }
    line[j] = '\0';
}