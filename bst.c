#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "bst.h"

int treeSize = 25; //global declariation of the nodes in the tree

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

//helper function to take a bst and return the parent array
void BSTtoParentArray(bst *t, int *parents){
    if(t->left != NULL){
        parents[t->left->item ] = t->item;
        BSTtoParentArray(t->left, parents);
    }
    if(t->right != NULL){
        parents[t->right->item ] = t->item;
        BSTtoParentArray(t->right, parents);
    }
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
/*
//Need a helper function for the first algorithm. findPath
//finds a path from root to target, if there is none
//then return false, otherwise store the path in path<int>
int findPath(bst *t, arraylist *path, int target) {
    //check if the tree is empty
    if(t == NULL) return -1;

    //store t in path
    add(path, t->item);

    //if the the current t->item is the target, return true
    if(t->item == target) return 1;

    //recursively check the left and right subtrees of t
    if( (t->left && findPath(t->left, path, target)) ||
        (t->right && findPath(t->right, path, target)) )
        return 1;

    //If target isn't present in t, remove t from path and
    //return false
    del(path, (getSize(path) - 1));
    return -1;
}

bst *lca1(bst *t, int n1, int n2)
{
    //make arraylists to store paths to n1 and n2 from root of t
    arraylist path1;
    init(&path1);
    arraylist path2;
    init(&path2);

    //find paths from root of t to n1 and root to n2,
    //if either are not present in t, return NULL
    if( findPath(t, &path1, n1) == 0 || findPath(t, &path2, n2) == 0 )
        return NULL;

    //compare the paths to get the first different value
    int i;
    for(i = 0; (i < getSize(&path1) && getSize(&path2)); i++) {
        if(get(&path1, i) != get(&path2, i)) break;
    }
    return get(&path1, i-1);
}*/


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

//LCA3
bst *lca3(bst *t){
    
}

//LCA4


int main() {
	//create runtime metrics
	clock_t begin, end;
	double time_spent;

    //create array
    int i;
    int arr[treeSize];
    for(i = 0; i < treeSize; i++){
        arr[i] = i;
    }
    //array to BST
    bst *a = NULL;
    a = sortedArrayToBST(arr, 0, (treeSize-1), a);
    //printTree(a);
    printf("\n");

    //LCA1
    int n1 = 0, n2 = (treeSize-1);
    bst *t;
    t = (bst *)malloc(sizeof(bst));
    /*t = lca1(a, n1, n2);
    printf("LCA1 of %d and %d is %d \n", n1, n2, t->item);

    n1 = 14, n2 = 8;
    t = lca1(a, n1, n2);
    printf("LCA1 of %d and %d is %d \n", n1, n2, t->item);

    n1 = 10, n2 = 22;
    t = lca1(a, n1, n2);
    printf("LCA1 of %d and %d is %d \n", n1, n2, t->item);
     */
    //LCA2
    n1 = 0, n2 = (treeSize-1);

    // Starts runtime
    begin = clock();

    //printf("The start time is %d\n",begin );

    t = lca2(a, n1, n2);

    // Ends runtime
    end = clock();

    //printf("The end time is %d\n",end);

    // Calculates the runtime in seconds
    // We multiply CLOCKS_PER_SEC by 1000 to accurately get the milliseconds

    time_spent = (double)(end - begin) / CLOCKS_PER_SEC * 1000;

    printf("The time to run the algorithm is %f\n", time_spent);


    printf("LCA2 of %d and %d is %d \n", n1, n2, t->item);

    n1 = 14, n2 = 8;
    t = lca2(a, n1, n2);
    printf("LCA2 of %d and %d is %d \n", n1, n2, t->item);

    n1 = 10, n2 = 22;
    t = lca2(a, n1, n2);
    printf("LCA2 of %d and %d is %d \n", n1, n2, t->item);

    //LCA3
    
    int p [treeSize];
    BSTtoParentArray(a, p);
    for(i = 0; i < treeSize; i++){
        printf("%d, ", p[i]);
    }

    //LCA4

    return 0;
}
