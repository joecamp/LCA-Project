#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include "bst.h"

int treeSize = 100; //global declariation of the nodes in the tree
//NOTE: For baseline, to get CPI & Latency, the treesize is 100
// to Show impact of treesize on runtime, Tree Size will be changed to 500, 750, 1000 & 1250.

//swap code
void swap (int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

//randomize/shuffle the values in a given array of n size
void randomize(int *arr, int n) {
    int i;
    srand (time(NULL));
    
    for (i = n-1; i > 0; i--){
        int j = rand() % (i+1);
        swap(&arr[i], &arr[j]);
    }
}

//adds a node of given value and parent to given bst
bst *bstAdd(bst *t, int x, bst *p) {
    //initialize node
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
        //otherwise, add to right
        if (t->item < x){
            t->right = bstAdd(t->right, x, t);
        }
        //otherwise, add to left
        else{
            t->left = bstAdd(t->left, x, t);
        }
    }
    return t;
}

//helper function to take a bst and return the parent array
//Pre-Condition: Assumes the only repeated values in the given bst are that of the root
//and its parent, where a root's parent's value is -1
void BSTtoParentArray(bst *t, int *p){
    if(t->parent == NULL){
        p[t->item] = -1;
    }
    
    if(t->left != NULL){
        p[t->left->item] = t->item;
        BSTtoParentArray(t->left, p);
    }
    
    if(t->right != NULL){
        p[t->right->item] = t->item;
        BSTtoParentArray(t->right, p);
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

//LCA2
bst *lca2(bst *t, int n1, int n2)
{
    // Check if t is NULL
    if(t == NULL) return NULL;

    // If t matches n1 or n2, return t
    if(t->item == n1 || t->item == n2) return t;

    // Recursively look for the LCA in the left and right subtrees of t
    bst *leftLCA  = lca2(t->left, n1, n2);
    bst *rightLCA = lca2(t->right, n1, n2);

    // If we get non-null returns from the left and right subtrees of t, then
    // n1 or n2 is present in the left subtree and n1 or n2 is present in the right
    // subtree, so t must be the LCA
    if(leftLCA && rightLCA) return t;

    // Otherwise check if left subtree or right subtree is LCA
    if(leftLCA != NULL) return leftLCA;
    else return rightLCA;
}

//LCA4
//Precondition: The given BST has no repeats and is full with distinct values 0..treeSize-1
int lca4(int *p, int n1, int n2){
    int i, j;
    int v1 = n1;
    int v2 = n2;
    int discovered[treeSize];
    //have an array to store the discovered states of the node
    for(i = 0 ; i < treeSize ; i++){
        discovered[i] = 0;
    }
    
    //loop executes until LCA is found
    while(1){
        //FOR FIRST VALUE
        //stop traversing if we hit the root of parent value -1
        if(v1 != -1){
            //check if the first value and its input has already been visted, then it is the LCA
            if(discovered[v1]) {
                return v1;
            }
            //otherwise mark it as discovered and traverse up the tree to its parent
            else{
                discovered[v1] = 1;
                v1 = p[v1];
            }
        }
        //FOR SECOND VALUE
        //stop traversing if we hit the root of parent value -1
        if(v2 != -1){
            //check if the second value and its input has already been vistied, then it is the LCA
            if(discovered[v2]) {
                return v2;
            }
            //otherwise mark it as discovered and traverse up the tree to its parent
            else{
                discovered[v2] = 1;
                v2 = p[v2];
            }
        }
        //if both v1 and v2 traverse up to the root, it is the LCA
        if((v1 == -1) && (v2 == -1)){
            return v1;
        }
    }
}


int main() {
	//create runtime metrics
	clock_t begin, end;
	double time_spent;

    //create array of 0..treeSize-1
    int i, j, l;
    int arr[treeSize];
    for(i = 0; i < treeSize; i++){
        arr[i] = i;
    }
    //randomize array
    randomize(arr, treeSize);
    
    //array to BST
    bst *a = NULL;
    for (i = 0; i < treeSize; i++) {
        a = bstAdd(a, arr[i], NULL);
    }
    
    
    //LCA2
    begin = clock();
    bst *t;
    t = (bst *)malloc(sizeof(bst));
    for(i = 0; i < treeSize; i ++){
        for (j = 0; j < treeSize; j++){
            t = lca2(a, i, j);
            printf("LCA2 of %d and %d is %d \n", i, j, t->item);
        }
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The time to run LCA2 is %f\n", time_spent);
    printf("\n");
    
    
    //LCA4
    begin = clock();
    int p[treeSize];
    BSTtoParentArray(a, p);
    for(i = 0; i < treeSize; i ++){
        for (j = 0; j < treeSize; j++){
            l = lca4(p, i, j);
            printf("LCA4 of %d and %d is %d \n", i, j, l);
        }
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The time to run LCA4 is %f\n", time_spent);
    printf("\n");
    
    return 0;
}
