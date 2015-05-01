#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

/*bst *bstAdd(bst *t, int x, bst *p) {
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
 }*/

//A function that constructs Balanced Binary Search Tree from a sorted array
bst* sortedArrayToBST(int arr[], int start, int end, bst *p)
{
    //Base Case
    if (start > end)
        return NULL;
    
    //Get the middle element and make it root
    int mid = (start + end)/2;
    bst *root;
    root = (bst *)malloc(sizeof(bst));
    root->item = arr[mid];
    root->left = NULL;
    root->right = NULL;
    root->parent = p;
    
    //Recursively construct the left subtree and make it
    //left child of root
    root->left =  sortedArrayToBST(arr, start, mid-1, root);
    
    //Recursively construct the right subtree and make it
    //right child of root
    root->right = sortedArrayToBST(arr, mid+1, end, root);
    
    return root;
}

void printTree(bst *t) {
    if(t != NULL) {
        printTree(t->left);
        printf("%d ", t->item);
        printTree(t->right);
    }
}

//LCA1
bst *lca1(bst *t, int n1, int n2) {
    while (t != NULL)
    {
        //If both n1 and n2 are greater than root, then LCA lies in left
        if (t->item > n1 && t->item > n2)
            t = t->left;
        
        //If both n1 and n2 are smaller than root, then LCA lies in right
        else if (t->item < n1 && t->item < n2)
            t = t->right;
        
        else break;
    }
    return t;
}


int main() {
    int i;
    int arr[50];
    for(i = 0; i < 50; i++){
        arr[i] = i;
    }
    bst *a = NULL;
    a = sortedArrayToBST(arr, 0, 49, NULL);
    printTree(a);
    printf("\n");
    
    //LCA1
    int n1 = 0, n2 = 49;
    bst *t;
    t = (bst *)malloc(sizeof(bst));
    t = lca1(a, n1, n2);
    printf("LCA1 of %d and %d is %d \n", n1, n2, t->item);
    
    n1 = 14, n2 = 8;
    t = lca1(a, n1, n2);
    printf("LCA1 of %d and %d is %d \n", n1, n2, t->item);
    
    n1 = 10, n2 = 22;
    t = lca1(a, n1, n2);
    printf("LCA1 of %d and %d is %d \n", n1, n2, t->item);
    
    return 0;
}