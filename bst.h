typedef struct bst {
  int item;                 /* data item */
  struct bst *parent;	    /* pointer to parent */
  struct bst *left;         /* pointer to left child */
  struct bst *right;		/* pointer to right child */
} bst;
