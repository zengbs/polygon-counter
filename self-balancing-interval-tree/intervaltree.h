#include<stdbool.h>
#include<stdlib.h>

typedef struct IntervalTreeNode TreeNode;

struct IntervalTreeNode {
   bool color;
   int leftend;
   int rightend;
   int max;
   int duplicate;
   TreeNode *parent;
   TreeNode *left;
   TreeNode *right;
};

extern TreeNode *neel;
