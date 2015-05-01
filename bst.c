#include <stdlib.h>
#include <stdio.h>
#include "bst.h"

/* A function that constructs Balanced Binary Search Tree from a sorted array */
bst* sortedArrayToBST(int arr[], int start, int end, bst *p)
{
    /* Base Case */
    if (start > end)
        return NULL;

    /* Get the middle element and make it root */
    int mid = (start + end)/2;
    bst *root;
    root = (bst *)malloc(sizeof(bst));
    root->item = arr[mid];
    root->left = NULL;
    root->right = NULL;
    root->parent = p;
    //bst *root = newNode(arr[mid]);

    /* Recursively construct the left subtree and make it
     left child of root */
    root->left =  sortedArrayToBST(arr, start, mid-1, root);

    /* Recursively construct the right subtree and make it
     right child of root */
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

/* Function to find LCA of n1 and n2. The function assumes that both
 n1 and n2 are present in BST */
bst *lca1(bst *t, int n1, int n2) {
    while (t != NULL)
    {
        // If both n1 and n2 are greater than root, then LCA lies in left
        if (t->item > n1 && t->item > n2)
            t = t->left;

        // If both n1 and n2 are smaller than root, then LCA lies in right
        else if (t->item < n1 && t->item < n2)
            t = t->right;

        else break;
    }
    return t;
}

/* Second function to find LCA of n1 and n2.  Assume that n1 and n2 are present in BST */
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
    int treeSize = 1000;
    int i;
    int arr[treeSize];
    for(i = 0; i < treeSize; i++){
        arr[i] = i;
    }
    bst *a = NULL;
    a = sortedArrayToBST(arr, 0, (treeSize-1), NULL);
    printTree(a);
    printf("\n");

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

    n1 = 0, n2 = (treeSize-1);
    t = lca2(a, n1, n2);
    printf("LCA2 of %d and %d is %d \n", n1, n2, t->item);

    n1 = 14, n2 = 8;
    t = lca2(a, n1, n2);
    printf("LCA2 of %d and %d is %d \n", n1, n2, t->item);

    n1 = 10, n2 = 22;
    t = lca2(a, n1, n2);
    printf("LCA2 of %d and %d is %d \n", n1, n2, t->item);

    return 0;
}
