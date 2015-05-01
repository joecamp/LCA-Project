#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

// Added a comment

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

//LCA2
bst *lca2(bst *t, int n1, int n2)
{
    // Check if t is NULL
    if (t == NULL) return NULL;
    
    // If t matches n1 or n2, return t
    if (t->item == n1 || t->item == n2)
        return t;
    
    // Recursively look for the LCA in the left and right subtrees of t
    bst *leftLCA  = lca2(t->left, n1, n2);
    bst *rightLCA = lca2(t->right, n1, n2);
    
    // If we get non-null returns from the left and right subtrees of t, then
    // n1 or n2 is present in the left subtree and n1 or n2 is present in the right
    // subtree, so t must be the LCA
    if (leftLCA && rightLCA)  return t;
    
    // Otherwise check if left subtree or right subtree is LCA
    if(leftLCA != NULL) return leftLCA;
    else return rightLCA;
}

int main() {
    //create array
    int treeSize = 1000;
    int i;
    int arr[treeSize];
    for(i = 0; i < treeSize; i++){
        arr[i] = i;
    }
    //array to BST
    bst *a = NULL;
    a = sortedArrayToBST(arr, 0, (treeSize-1), NULL);
    printTree(a);
    printf("\n");

    //LCA1
    int n1 = 0, n2 = (treeSize-1);
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
    n1 = 0, n2 = (treeSize-1);
    t = lca2(a, n1, n2);
    printf("LCA2 of %d and %d is %d \n", n1, n2, t->item);

    n1 = 14, n2 = 8;
    t = lca2(a, n1, n2);
    printf("LCA2 of %d and %d is %d \n", n1, n2, t->item);

    n1 = 10, n2 = 22;
    t = lca2(a, n1, n2);
    printf("LCA2 of %d and %d is %d \n", n1, n2, t->item);
    
    //LCA3
    
    //LCA4

    return 0;
}
