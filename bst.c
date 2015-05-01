#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

bst* bstInit(bst *t, int value, bst *parent) {
    t->item = value;
    t->left = NULL;
    t->right = NULL;
    t->parent = parent;
}

int bstAdd(bst *t, int x) {
    if(t->item != x) {
        if(t->item < x) {
            if(t->right != NULL) {
                bstAdd(t->right, x);
            }
            else {
                t->right->parent = t;
                t->right->item = x;
                t->right->right = NULL;
                t->right->left = NULL;
                return 1;
            }
        }
        if(t->item > x) {
            if(t->left != NULL) {
                bstAdd(t->left, x);
            }
            else {
                bst left;
                bstInit(&left, x, t);
                t->left = &left;
                return 1;
            }
        }
    }
    else return 0;
}

void printTree(bst *t) {
    if(t != NULL) {
        printTree(t->left);
        printf("%d ", t->item);
        printTree(t->right);
    }
}

int main() {
    bst a;
    fflush(stdout);
    bstInit(&a, 5, &a);
    fflush(stdout);
    bstAdd(&a, 3);
    printTree(&a);
    return 0;
}
