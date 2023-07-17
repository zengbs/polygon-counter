#include<stdbool.h>
#include<stdlib.h>

typedef struct RBTreeNode TreeNode;

struct RBTreeNode {
   bool color;
   int key;
   int duplicate;
   TreeNode *parent;
   TreeNode *left;
   TreeNode *right;
};

extern TreeNode *neel;
