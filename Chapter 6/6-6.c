/*
    Implement DEFINE!

    We can leverage all the function created in ex. 6-5:

        - get a word (while there are words)
        - check if that word is "DEFINE"
            - if it is, flag that the next word will be installed in the hashtable
        - check if the word is present in the hashtable
            - if it is, set the word to copy to the output to the defn
        - output the word that needs to be outputted.
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define WORD_LEN 100
#define HASHSIZE 101
#define TRUE 1
#define FALSE 0

struct nlist {              // table entry
    struct nlist *next;     // next entry in chain
    char *name;             // defined name
    char *defn;             // replacement text
};

char word[WORD_LEN];

int getword();
struct nlist *install(char *name, char *defn);
struct nlist *lookup(char *s);

int main()
{
    int signal;
    int name_flag, defn_flag;
    int is_valid_word;
    struct nlist * tmp;

    char name[WORD_LEN];

    name_flag = FALSE;

    while ((signal = getword()) != EOF){

        is_valid_word = signal != ' ' && signal != '\n' && signal != '\t';

        if ((tmp = lookup(word)) == NULL)
            printf("%s", word);
        else
            printf("%s", tmp->defn);

        if (defn_flag == TRUE && is_valid_word){
            install(name, word);
            defn_flag = FALSE;
        }

        if (name_flag == TRUE && is_valid_word){
            strcpy(name, word);
            name_flag = FALSE;
            defn_flag = TRUE;
        }


        if (strcmp(word, "DEFINE") == 0)
            name_flag = TRUE;

    }

    return 0;
}

static struct nlist *hashtab[HASHSIZE]; // pointer table

/* hash:    form hash value for string s */
unsigned hash(char *s)
{
    unsigned hashval;

    for (hashval = 0; *s != '\0'; s++)
        hashval = *s + 31 * hashval;
    
    return hashval % HASHSIZE;
}

/* lookup:  look for s in hashtab */
struct nlist *lookup(char *s)
{
    struct nlist *np;

    for (np = hashtab[hash(s)]; np != NULL; np = np->next)
        if (strcmp(s, np->name) == 0)
            return np;  // found
        
    return NULL;    // not found
}

/* install: put (name, defn) in hashtab */
struct nlist *install(char *name, char *defn)
{
    struct nlist *np;
    unsigned hashval;

    if ((np = lookup(name)) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));

        if (np == NULL || (np->name = strdup(name)) == NULL)
            return NULL;

        hashval = hash(name);           // create an hash for the name
        np->next = hashtab[hashval];    // insert np at the beginning of the list present at hashtab[hashval]
        hashtab[hashval] = np;          // set np to be the first node of the list
    } else
        free((void *) np->defn);

    if ((np->defn = strdup(defn)) == NULL)
        return NULL;

    return np;
}

/* getword: get every single word of the input.
            Spaces and new lines are considered words */
int getword()
{   
    int c;
    char * word_ptr = word;
    while ((c = getchar()) != EOF){
        if (c == '\n' || c == ' ' || c == ';' || c == ')'  || c == ']' || c == '}')
            if (word_ptr == word){
                *word_ptr++ = c;
                *word_ptr = '\0';
                return c;
            }
            else{
                ungetc(c, stdin);
                return word[0];
            }

        if (c == '#' || c == '('  || c == '[' || c == '{'){
            *word_ptr++ = c;
            *word_ptr = '\0';
            return c;
        }

        *word_ptr++ = c;
        *word_ptr = '\0';
    }

    return EOF;
}