#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define MAXWORD 100

struct tnode {          /* the tree node */
    char *word;             /* points to the text */
    int count;              /* counter for word occurrences */ 
    struct tnode *left;     /* left child */
    struct tnode *right;    /* right child */
};

int getword(char *word, int lim);
struct tnode *addtree(struct tnode *t, char *w);
int get_n_of_elements(struct tnode *t);
void build_tree_array(struct tnode *array[], struct tnode *tree);
int node_compare(struct tnode *a, struct tnode *b);

int main()
{
    int c;
    char word[MAXWORD];
    struct tnode *tree = NULL;

    // Add all words to the tree
    while ((c = getword(word, MAXWORD) != EOF))
        tree = addtree(tree, word);

    // Build an array with all tree elements
    int n_tree_elements = get_n_of_elements(tree);
    struct tnode *treearray[n_tree_elements];
    build_tree_array(treearray, tree);

    // Sort the array in decreasing order of occurrencies
    qsort(treearray, n_tree_elements, sizeof(struct tnode *), (int (*)(const void *, const void *)) node_compare);

    // Print the sorted array in reverse order
    for (int i = n_tree_elements-1; i >= 0; i--)
        printf("Occurrences: %d\tword: %s\n", treearray[i]->count, treearray[i]->word);

    return 0;
}

/* getword: get next word or character from input */
int getword(char *word, int lim)
{
    int c, tmp, getch(void);
    void ungetch(int);
    char *w = word;

    while (isspace(c = getch()))
        ;
    
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

/* addtree:     add a node with w, at or below p */
struct tnode *addtree(struct tnode *p, char *w)
{
    if (p == NULL){
        p = (struct tnode *) malloc(sizeof(struct tnode));
        p->word = strdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if (strcmp(w, p->word) == 0){
        p->count++;
    } else if (strcmp(w, p->word) < 0)
        p->left = addtree(p->left, w);
    else
        p->right = addtree(p->right, w);

    return p;
}

/* get_n_of_elements: return the number of elements that constitute t */
int get_n_of_elements(struct tnode *t)
{
    if (t == NULL)
        return 0;

    return 1 + get_n_of_elements(t->left) + get_n_of_elements(t->right);
}

/* build_tree_array:    insert in array the pointers to all nodes of tree */
void build_tree_array(struct tnode *array[], struct tnode *tree)
{
    static int index = 0;

    if (tree != NULL){
        array[index++] = tree;
        build_tree_array(array, tree->left);
        build_tree_array(array, tree->right);
    }
}

/* node_compare: return 1 if a > b, 0 if a = b and -1 if a < b */
int node_compare(struct tnode *a, struct tnode *b)
{
    if (a->count > b->count)
        return 1;
    else if (a->count < b->count)
        return -1;
    else
        return 0;
}