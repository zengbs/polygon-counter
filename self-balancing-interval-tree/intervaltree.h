#include<stdbool.h>
#include<stdlib.h>





typedef struct Interval{
   int low;
   int high;
} Interval;

typedef struct IntervalTreeNode TreeNode;

struct IntervalTreeNode {
   bool color;
   int low;
   int high;
   int max;
   int duplicate;
   TreeNode *parent;
   TreeNode *left;
   TreeNode *right;
};

extern TreeNode *neel;
