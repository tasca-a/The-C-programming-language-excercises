#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include "utils.h"

#define debug(message) (printf("%s\n", message))

#define MAXWORD 100
#define TRUE 1
#define FALSE 0

static int EQUALCHAR = 6;

struct tnode {          /* the tree node */
    char *word;             /* points to the text */    
    struct tnode *left;     /* left child */
    struct tnode *right;    /* right child */
};

struct vargroup {       /* a group of variable names */
    struct tnode *tree;     /* points to the tree of the group */
    struct vargroup *nextg; /* points to the next group of var names */
};

void process_arguments(int argc, char **argv);
int getword(char *word, int lim);
int skipbetween(int start, int end);
int isvarname(char *word);
struct tnode *addtree(struct tnode *p, char *w);
void treeprint(struct tnode *p);
struct vargroup *addgroup(struct vargroup *g, char *word);
void groupprint(struct vargroup *g);
struct vargroup * addwordtogroup(struct vargroup *g, char *w);

int main(int argc, char **argv)
{
    process_arguments(argc, argv);
    
    int c;
    char word[MAXWORD];
    int count = 0;
    struct vargroup *groups = NULL;
    while ((c = getword(word, MAXWORD)) != EOF){
        if (isvarname(word)){
            groups = addwordtogroup(groups, word);
        }
    }

    groupprint(groups);

    return 0;
}

/* process_arguments:   process the program arguments to update the number of
                        characters that has to be equal to list */
void process_arguments(int argc, char **argv)
{
    int tmp = 0;

    while (argc-- > 1){
        if (*(++argv)[0] == '-')
            tmp = atoi(&(*argv)[1]);
    }

    if (tmp > 0)
        EQUALCHAR = tmp;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, tmp, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    
    if (c != EOF){
        while (c == '"' || c == '\'' || c == '/' || c == '#'){
            switch (c) {
                case '"': ungetch(c); c = skipbetween('"', '"'); break;         // skip all strings
                case '\'': ungetch(c); c = skipbetween('\'', '\''); break;      // skip all chars
                case '/':
                    tmp = getch();
                    if (tmp == '/'){
                        ungetch(tmp);
                        c = skipbetween('/', '\n');                             // skip all inline comments
                    } else if (tmp == '*'){
                        ungetch(tmp);

                        while ((c = skipbetween('*', '*')) != '/')              // skip all multiline comments
                            ;

                        while (isspace(c = getch()))    // remove all spaces afterwards 
                            ;
                    }
                    break;                    
                case '#': ungetch(c); c = skipbetween('#', '\n'); break;        // skip all preprocessor directives
            }
        }
        *w++ = c;
    }

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

/* skipbetween: skip all characters starting at start and ending at end.
                returns the first character after skipping. */
int skipbetween(int start, int end)
{
    int c;

    if ((c = getch()) != start){
        ungetch(c);
        return c;
    }

    while ((c = getch()) != end)    // skips all characters in between..
        ;

    while (isspace(c = getch()))    // skips all the spaces after the end
        ;

    return c;
}

/* isvarname:   return 1 if the word passed is a varname, 0 if it's not */
int isvarname(char *word)
{
    static int VAR_FLAG = FALSE;
    static char *type[] = {"int", "char", "float", "double", NULL};

    if (VAR_FLAG == TRUE){
        if (strcmp(word, ";") == 0){
            VAR_FLAG = FALSE;
            return FALSE;
        }

        if (!isalnum(word[0])){
            return FALSE;
        }

        return TRUE;
    }

    for (int i = 0; type[i] != NULL; i++)
        if (strcmp(word, type[i]) == 0)
            VAR_FLAG = TRUE;

    return FALSE;
}

/* addtree:     add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    if (p == NULL){
        p = (struct tnode *) malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->left = p->right = NULL;
    } else if (strcmp(w, p->word) <= 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

/* treeprint:   in-order print of tree p */
void treeprint(struct tnode *p)
{
    if (p != NULL){
        treeprint(p->left);
        printf("%s\n", p->word);
        treeprint(p->right);
    }
}

/* addgroup:    add a group with tree at g */
struct vargroup *addgroup(struct vargroup *g, char *word)
{
    if (g != NULL){
        //printf("RECURSIVE?\n");
        return g = addgroup(g->nextg, word);
    }

    //printf("stai allocando vero?\n");
    g = (struct vargroup *) malloc(sizeof(struct vargroup));    // allocate memory for the new group

    struct tnode *tree = NULL;      // create a new tree
    g->tree = addtree(tree, word);  // add the tree to the group with the new word inside it
    g->nextg = NULL;                // the next tree is set to null

    return g;
}

/* groupprint:  print of all groups */
void groupprint(struct vargroup *g)
{
    static int count = 1;

    if (g != NULL){
        printf("group %d:\n", count++);
        treeprint(g->tree);
        groupprint(g->nextg);
    } else 
        count = 1;
}

/* addwordtogroup:  add w to the group g recursively */
struct vargroup *addwordtogroup(struct vargroup *g, char *w)
{
    if (g == NULL)
        g = addgroup(g, w);
    else
        if (strncmp(w, g->tree->word, EQUALCHAR) == 0)
            g->tree = addtree(g->tree, w);
        else
            g->nextg = addwordtogroup(g->nextg, w);

    return g;
}