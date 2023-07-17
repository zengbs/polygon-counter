#include<stdbool.h>
#include<stdlib.h>

typedef struct RBTNode TreeNode;

struct RBTNode {
   bool color;
   int leftend;
   int duplicate;
   TreeNode *parent;
   TreeNode *left;
   TreeNode *right;
};

extern TreeNode *neel;
