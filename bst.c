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

/*//LCA1
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
}*/

// This function returns pointer to LCA of two given values n1 and n2.
// This function assumes that n1 and n2 are present in Binary Tree
bst *lca1(bst *root, int n1, int n2)
{
    // Base case
    if (root == NULL) return NULL;
    
    // If either n1 or n2 matches with root's key, report
    // the presence by returning root (Note that if a key is
    // ancestor of other, then the ancestor key becomes LCA
    if (root->item == n1 || root->item == n2) return root;
    
    // Look for keys in left and right subtrees
    bst *left_lca  = lca1(root->left, n1, n2);
    bst *right_lca = lca1(root->right, n1, n2);
    
    // If both of the above calls return Non-NULL, then one key
    // is present in once subtree and other is present in other,
    // So this node is the LCA
    if (left_lca && right_lca)  return root;
    
    // Otherwise check if left subtree or right subtree is LCA
    return (left_lca != NULL)? left_lca: right_lca;
}


int main() {
    //create array
    int i;
    int arr[50];
    for(i = 0; i < 50; i++){
        arr[i] = i;
    }
    //array to BST
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
    
    //LCA2
    
    //LCA3
    
    //LCA4
    
    return 0;
}