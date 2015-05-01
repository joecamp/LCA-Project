#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

//Constructs Balanced Binary Search Tree from a sorted array
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
    
    //Recursively construct the left subtree and make it the left child of root
    root->left =  sortedArrayToBST(arr, start, mid-1, root);
    
    //Recursively construct the right subtree and make it the right child of root
    root->right = sortedArrayToBST(arr, mid+1, end, root);
    
    return root;
}

//print tree inorder
void printTree(bst *t) {
    if(t != NULL) {
        printTree(t->left);
        printf("%d ", t->item);
        printTree(t->right);
    }
}

//LCA functions assume that n1 and n2 are present in Binary Tree

//LCA1
bst *lca1(bst *root, int n1, int n2)
{
    // Base case
    if (root == NULL){
        return NULL;
    }
    
    // If either n1 or n2 matches with root's key, report
    // the presence by returning root (Note that if a key is
    // ancestor of other, then the ancestor key becomes LCA
    if (root->item == n1 || root->item == n2){
        return root;
    }
    
    // Look for keys in left and right subtrees
    bst *left_lca  = lca1(root->left, n1, n2);
    bst *right_lca = lca1(root->right, n1, n2);
    
    // If both of the above calls return Non-NULL, then one key
    // is present in once subtree and other is present in other,
    // So this node is the LCA
    if ((left_lca != NULL) && (right_lca != NULL)){
        return root;
    }
    
    // Otherwise check if left subtree or right subtree is LCA
    if(left_lca != NULL){
        return left_lca;
    }
    else{
        return right_lca;
    }
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