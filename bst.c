#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

bst *bstAdd(bst *t, int x, bst *p) {
    if(t == NULL){
        bst *added;
        added = (bst *)malloc(sizeof(bst));
        added->item = x;
        added->left = NULL;
        added->right = NULL;
        added->parent = p;
        return added;
    }
    else if(t->item != x){
        if (t->item < x){
            t->right = bstAdd(t->right, x, t);
        }
        else{
            t->left = bstAdd(t->left, x, t);
        }
        
    }
    return t;
}

void printTree(bst *t) {
    if(t != NULL) {
        printTree(t->left);
        printf("%d ", t->item);
        printTree(t->right);
    }
}

int main() {
    int i;
    bst *a = NULL;
    for(i = 0; i < 50; i++){
        a = bstAdd(a, i, NULL);
    }
    printTree(a);
    return 0;
}
