#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100
#define FUZZ_LENGTH (sizeof(FUZZ)/sizeof(FUZZ[0]))

static char *FUZZ[] = {
    "and",
    "the",
    "of"
    // you can add anything
};

struct list{
    int line_number;
    struct list *next;
};

struct tnode {          /* the tree node */
    char *word;             /* points to the text */
    struct list *lines;     /* points to the list of line numbers */  
    struct tnode *left;     /* left child */
    struct tnode *right;    /* right child */
};

static int LINE_NUMBER = 1;

int getword(char *word, int lim);
int isfuzz(char *word);
struct tnode *addtree(struct tnode *p, char *w);
struct list *addlist(struct list *l, int line_number);
void treeprint(struct tnode *p);
void listprint(struct list *l);

int main()
{
    int c;
    char word[MAXWORD];
    struct tnode *words = NULL;

    while ((c = getword(word, MAXWORD) != EOF)){
        if (!isfuzz(word)){
            words = addtree(words, word);
        }
    }

    treeprint(words);

    return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, tmp, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch())){
        if (c == '\n')
            LINE_NUMBER++;
    }
    
    if (c != EOF)
        *w++ = c;

    if (!isalpha(c) && c != '_'){
        *w = '\0';
        return c;
    }

    while (--lim > 0){
        if (!isalnum(*w = getch()) && *w != '_'){
            ungetch(*w);
            break;
        }
        w++;
    }
    *w = '\0';

    return word[0];
}

/* isfuzz:  return 1 if word is a fuzz word, 0 if it's not */
int isfuzz(char *word)
{
    for (int c = 0; c < FUZZ_LENGTH; c++)
        if (strcmp(word, FUZZ[c]) == 0)
            return 1;
    
    return 0;
}

/* addtree:     add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    if (p == NULL){
        p = (struct tnode *) malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->left = p->right = NULL;

        p->lines = NULL;
        p->lines = addlist(p->lines, LINE_NUMBER);
    } else if (strcmp(w, p->word) == 0){
        p->lines = addlist(p->lines, LINE_NUMBER);
    } else if (strcmp(w, p->word) < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

/* addlist:     add a list with line_number if is not already present */
struct list *addlist(struct list *l, int line_number)
{
    if (l == NULL){
        l = (struct list *) malloc(sizeof(struct list));
        l->line_number = line_number;
        l->next = NULL;
    } else  if (l->line_number != line_number)
        l->next = addlist(l->next, line_number);
        
    return l;
}

/* treeprint:   in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL){
        treeprint(p->left);

        printf("word %s occurrences in lines:\n", p->word);
        listprint(p->lines);

        treeprint(p->right);
    }
}

/* listprint:   in-order print of list l */
void listprint(struct list *l)
{
    if (l != NULL){
        printf("%d%s", l->line_number, (l->next != NULL) ? ", " : "\n");
        listprint(l->next);
    }
}