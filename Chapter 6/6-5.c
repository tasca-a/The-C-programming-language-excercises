#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define HASHSIZE 101
#define FOUND "FOUND"
#define NOTFOUND "NOT FOUND"

struct nlist {              // table entry
    struct nlist *next;     // next entry in chain
    char *name;             // defined name
    char *defn;             // replacement text
};

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

/* undef:   remova a name and definition from the table */
void undef(char *name)
{
    unsigned hashval = hash(name); 

    struct nlist *np = hashtab[hashval];

    struct nlist *next;
    for (struct nlist *ptr = np; ptr != NULL; ptr = next){
        next = ptr->next;
        free((void *) ptr);
    }

    hashtab[hashval] = NULL;
}

int main()
{
    printf("Defining name \"%s\" with definition \"%s\"\n", "Alessandro", "Puzza");
    printf("Defining name \"%s\" with definition \"%s\"\n", "Giorgia", "Marrone");
    printf("Defining name \"%s\" with definition \"%s\"\n", "Alberto", "Gioco di ruolo");
    printf("Defining name \"%s\" with definition \"%s\"\n", "Alessandro", "Soffia");

    install("Alessandro", "Puzza");
    install("Giorgia", "Marrone");
    install("Alberto", "Gioco di ruolo");
    install("Alessandro", "Soffia");

    printf("Checking the table status..\n");
    printf("...searching for %s: %s\n", "Alessandro", (lookup("Alessandro") != NULL) ? FOUND : NOTFOUND);
    printf("...searching for %s: %s\n", "Giorgia", (lookup("Giorgia") != NULL) ? FOUND : NOTFOUND);
    printf("...searching for %s: %s\n", "Alberto", (lookup("Alberto") != NULL) ? FOUND : NOTFOUND);

    printf("Testing undef function by removing \"Alberto\"..\n");
    undef("Alberto");

    printf("Checking the table status again..\n");
    printf("...searching for %s: %s\n", "Alessandro", (lookup("Alessandro") != NULL) ? FOUND : NOTFOUND);
    printf("...searching for %s: %s\n", "Giorgia", (lookup("Giorgia") != NULL) ? FOUND : NOTFOUND);
    printf("...searching for %s: %s\n", "Alberto", (lookup("Alberto") != NULL) ? FOUND : NOTFOUND);


    return 0;
}