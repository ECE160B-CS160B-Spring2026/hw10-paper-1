#include <stdio.h>
#include <stdlib.h>

#define HASH_SIZE 101

struct nlist {
    struct nlist *next;
    int data;
};

static struct nlist *hashtab[HASH_SIZE]; 

unsigned hash(int n) {
    return (unsigned)abs(n) % HASH_SIZE;
}

struct nlist *lookup(int n) {
    struct nlist *np;
    for (np = hashtab[hash(n)]; np != NULL; np = np->next) {
        if (n == np->data)
            return np;
    }
    return NULL;
}

void install(int n) {
    struct nlist *np;
    unsigned hashval;
    if (lookup(n) == NULL) {
        np = (struct nlist *) malloc(sizeof(*np));
        np->data = n;
        hashval = hash(n);
        np->next = hashtab[hashval];
        hashtab[hashval] = np;
    }
}

void delete_node(int n) {
    struct nlist *np, *prev = NULL;
    unsigned h = hash(n);
    for (np = hashtab[h]; np != NULL; np = np->next) {
        if (np->data == n) {
            if (prev == NULL) hashtab[h] = np->next;
            else prev->next = np->next;
            free(np);
            return;
        }
        prev = np;
    }
}

void intersection(int output[], int array1[], int lenArr1, int array2[], int lenArr2) {
    int i, k = 0;

    for (i = 0; i < lenArr1; i++) {
        install(array1[i]);
    }

    for (i = 0; i < lenArr2; i++) {
        if (lookup(array2[i]) != NULL) {
            output[k++] = array2[i];
            delete_node(array2[i]); 
        }
    }
    
    output[k] = -999999; 
}

int main() {
    int n1, n2, i;

    if (scanf("%d", &n1) != 1) return 0;
    int *arr1 = malloc(n1 * sizeof(int));
    for (i = 0; i < n1; i++) scanf("%d", &arr1[i]);

    if (scanf("%d", &n2) != 1) return 0;
    int *arr2 = malloc(n2 * sizeof(int));
    for (i = 0; i < n2; i++) scanf("%d", &arr2[i]);

    int *out = malloc((n1 < n2 ? n1 : n2 + 1) * sizeof(int));

    intersection(out, arr1, n1, arr2, n2);

    for (i = 0; out[i] != -999999; i++) {
        printf("%d%s", out[i], (out[i+1] == -999999) ? "" : " ");
    }
    printf("\n");

    free(arr1);
    free(arr2);
    free(out);
    return 0;
}