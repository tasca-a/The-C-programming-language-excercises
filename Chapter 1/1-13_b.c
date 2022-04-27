#include <stdio.h>

#define BUF_LENGHT 100
#define IN 1
#define OUT 0

int main(){

    int word_lenght[BUF_LENGHT];

    for (int i = 0; i < BUF_LENGHT; i++)
        word_lenght[i] = 0;

    int c;
    int word = 0;
    int state = OUT;

    while ((c = getchar()) != EOF && word < BUF_LENGHT){
        if (c == ' ' || c == '\n' || c =='\t'){
            state = OUT;
            word++;
        } else
        if (state = OUT){
            state = IN;
            word_lenght[word]++;
        } else
            word_lenght[word]++;
    }

    // Cerco la parola con più caratteri.
    // La sua lunghezza sarà l'altezza totale delle colonne.
    // Per ogni riga dell'altezza, controllo se la corrispettiva parola deve mettere o no il segno dell'istogramma.
    // Alla fine di tutto metto il numero della parola sotto ogni colonna.

    int max = 0;
    for (int i = 0; i <= word; i++)
        if (word_lenght[i] > max)
            max = word_lenght[i];
    
    for (int scanline = max; scanline > 0; scanline--){
        for (int i = 0; i <= word; i++){
            if (word_lenght[i] >= scanline)
                printf("#\t");
            else
                printf("\t");
        }
        putchar('\n');
    }
    for (int i = 0; i <= word; i++)
        printf("word %d\t", i);
}