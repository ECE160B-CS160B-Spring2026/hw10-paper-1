#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAXWORD 100

struct tnode {
    char *word;
    int count;
    struct tnode *left;
    struct tnode *right;
};

struct tnode *addtree(struct tnode *, char *);
struct tnode *add_count_tree(struct tnode *, struct tnode *);
struct tnode *build_count_tree(struct tnode *, struct tnode *);
void treeprint_descending(struct tnode *);
int getword(char *, int);
struct tnode *talloc(void);
char *mystrdup(char *);

int main() {
    struct tnode *root = NULL;
    struct tnode *count_root = NULL;
    char word[MAXWORD];

    while (getword(word, MAXWORD) != EOF) {
        if (isalpha(word[0])) {
            root = addtree(root, word);
        }
    }

    count_root = build_count_tree(root, count_root);

    treeprint_descending(count_root);

    return 0;
}

struct tnode *addtree(struct tnode *p, char *w) {
    int cond;
    if (p == NULL) {
        p = talloc();
        p->word = mystrdup(w);
        p->count = 1;
        p->left = p->right = NULL;
    } else if ((cond = strcmp(w, p->word)) == 0) {
        p->count++;
    } else if (cond < 0) {
        p->left = addtree(p->left, w);
    } else {
        p->right = addtree(p->right, w);
    }
    return p;
}

struct tnode *build_count_tree(struct tnode *p, struct tnode *count_root) {
    if (p != NULL) {
        count_root = build_count_tree(p->left, count_root);
        count_root = build_count_tree(p->right, count_root);
        
        p->left = p->right = NULL; 
        count_root = add_count_tree(count_root, p);
    }
    return count_root;
}

struct tnode *add_count_tree(struct tnode *p, struct tnode *new_node) {
    if (p == NULL) {
        p = new_node;
    } else if (new_node->count >= p->count) {
        p->left = add_count_tree(p->left, new_node);
    } else {
        p->right = add_count_tree(p->right, new_node);
    }
    return p;
}

void treeprint_descending(struct tnode *p) {
    if (p != NULL) {
        treeprint_descending(p->left);
        printf("%d %s\n", p->count, p->word);
        treeprint_descending(p->right);
    }
}

struct tnode *talloc(void) {
    return (struct tnode *) malloc(sizeof(struct tnode));
}

char *mystrdup(char *s) {
    char *p = (char *) malloc(strlen(s) + 1);
    if (p != NULL) strcpy(p, s);
    return p;
}

int getword(char *word, int lim) {
    int c, getch(void);
    void ungetch(int);
    char *w = word;
    while (isspace(c = getch()));
    if (c != EOF) *w++ = c;
    if (!isalpha(c)) {
        *w = '\0';
        return c;
    }
    for (; --lim > 0; w++) {
        if (!isalnum(*w = getch())) {
            ungetch(*w);
            break;
        }
    }
    *w = '\0';
    return word[0];
}

#define BUFSIZE 100
char buf[BUFSIZE];
int bufp = 0;
int getch(void) { return (bufp > 0) ? buf[--bufp] : getchar(); }
void ungetch(int c) { if (bufp < BUFSIZE) buf[bufp++] = c; }