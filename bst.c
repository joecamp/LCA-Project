#include <stdlib.h>
#include "bst.h"

//typedef struct bst {
//  int item;			/* data item */
//  struct bst *parent;	    /* pointer to parent */
//  struct bst *left;		/* pointer to left child */
//  struct bst *right;		/* pointer to right child */
//} bst;

bst* bstInit(bst *t, int value, bst *parent) {
    t->item = value;
    t->left = NULL;
    t->right = NULL;
    t->parent = parent;
}

void printTree(bst *t) {
    if(t != NULL) {
        printTree(t->left);
        printf("%d", t->item);
        printTree(t->right);
    }
}

int main() {
    bst a;
    bstInit(&a, 5, &a);
    printTree(&a);
    return 0;
}
