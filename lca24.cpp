// A O(n) solution to find LCA of two given values n1 and n2
#include <iostream>
#include <algorithm>
#include <time.h>
#include <vector>
using namespace std;

int treeSize = 100;
//NOTE: For baseline, to get CPI & Latency, the treesize is 100
// to Show impact of treesize on runtime, Tree Size will be changed to 500, 750, 1000 & 1250.
// A Binary Tree node
struct Node
{
    int item;
    struct Node *left, *right, *parent;
};

// Utility function creates a new binary tree node with given item
Node * newNode(int k, Node *parent)
{
    Node *temp = new Node;
    temp->item = k;
    temp->left = temp->right = NULL;
    temp->parent = parent;
    return temp;
}

void nodeAdd(Node *root, int k) {
    if(root == NULL) {
        root = newNode(k, root);
    }
    else {
        if(root->item <= k) {
            if(root->left == NULL) {
                root->left = newNode(k, root);
            }
            else nodeAdd(root->left, k);
        }
        if(root->item >= k) {
            if(root->right == NULL) {
                root->right = newNode(k, root);
            }
            else nodeAdd(root->right, k);
        }
    }
}

//helper function to take a bst and return the parent array
//Pre-Condition: Assumes the only repeated values in the given bst are that of the root
//and its parent, where a root's parent's value is -1
void BSTtoParentArray(Node *t, int *p){
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

void shuffle(int *array, size_t n) {
    if (n > 1) {
        size_t i;
	for (i = 0; i < n - 1; i++) {
	  size_t j = i + rand() / (RAND_MAX / (n - i) + 1);
	  int t = array[j];
	  array[j] = array[i];
	  array[i] = t;
	}
    }
}

// Finds the path from root node to given root of the tree, Stores the
// path in a vector path[], returns true if path exists otherwise false
bool findPath(Node *root, vector<int> &path, int k)
{
    // base case
    if (root == NULL) return false;

    // Store this node in path vector. The node will be removed if
    // not in path from root to k
    path.push_back(root->item);

    // See if the k is same as root's item
    if (root->item == k)
        return true;

    // Check if k is found in left or right sub-tree
    if ( (root->left && findPath(root->left, path, k)) ||
         (root->right && findPath(root->right, path, k)) )
        return true;

    // If not present in subtree rooted with root, remove root from
    // path[] and return false
    path.pop_back();
    return false;
}

// Returns LCA if node n1, n2 are present in the given binary tree,
// otherwise return -1
int lca1(Node *root, int n1, int n2)
{
    // to store paths to n1 and n2 from the root
    vector<int> path1, path2;

    // Find paths from root to n1 and root to n1. If either n1 or n2
    // is not present, return -1
    if ( !findPath(root, path1, n1) || !findPath(root, path2, n2))
          return -1;

    /* Compare the paths to get the first different value */
    int i;
    for (i = 0; i < path1.size() && i < path2.size() ; i++)
        if (path1[i] != path2[i])
            break;
    return path1[i-1];
}

//LCA3
int lca3(int *p, int n1, int n2) {
    vector<int> path;
    int i = n1;
    //from n1, walk up to the root using the parent array
    while(p[i] != i) { //keep going until we hit the root
        path.push_back(i); //store the values in path
        i = p[i];
    }
    path.push_back(i);

    //then, from n2, walk up to the root using the parent array
    //until we hit a node that matches something in path
    int j = n2;
    while(p[j] != -1) { //keep going until we hit the root
        for(i = 0; i < path.size(); i++) { //check all the items in path
          if(path[i] == j) return j;
        }
        j = p[j];
    }
}

// Driver program to test above functions
int main()
{
    clock_t begin, end;
    double time_spent;
    int i, j, l;

    int arr[treeSize];
    for(i = 0; i < treeSize; i++) {
        arr[i] = i;
    }

    random_shuffle(&arr[0], &arr[treeSize]);

    /*for(i = 0; i < treeSize; i++) {
        cout << arr[i];
        cout << "\n";
    }*/

    Node *root = newNode(0, NULL);

    for(i = 0; i < treeSize; i++) {
        nodeAdd(root, arr[i]);
    }
    
    //LCA1
    begin = clock();
    for(i = 0; i < treeSize; i++) {
        for(j = 0; j < treeSize; j++) {
            l = lca1(root, i, j);
         //   cout << "LCA1 of " << i << " and " << j << " is " << l;
         //   cout << "\n";
        }
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "The time to run LCA1 is " << time_spent;
    cout << "\n";

    //LCA3
    begin = clock();
    int p[treeSize];
    BSTtoParentArray(root, p);
    for(i = 0; i < treeSize; i++) {
        for(j = 0; j < treeSize; j++) {
            l = lca3(p, i, j);
      //      cout << "LCA3 of " << i << " and " << j << " is " << l;
        //    cout << "\n";
        }
    }
    end = clock();
    time_spent = (double)(end - begin) / CLOCKS_PER_SEC;
    cout << "\nThe time to run LCA3 is " << time_spent;
    cout << "\n";

    return 0;
}
