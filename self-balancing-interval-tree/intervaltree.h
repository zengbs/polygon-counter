#include<stdbool.h>
#include<stdlib.h>


typedef struct Interval{
   int low;
   int high;
} Interval;


typedef struct ListNode ListNode;
struct ListNode {
   int key;
   ListNode *next;
   ListNode *prev;
};

typedef struct IntervalTreeNode TreeNode;
struct IntervalTreeNode {
   bool color;
   int low;
   ListNode *highList;
   ListNode *countedList;
   int listLength;
   int max;
   TreeNode *parent;
   TreeNode *left;
   TreeNode *right;
};

extern TreeNode *neel;
extern TreeNode *root;
