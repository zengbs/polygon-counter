#include<stdbool.h>
#include<stdlib.h>


typedef struct Interval{
   int low;
   int high;
   bool counted;
} Interval;


typedef struct ListNode ListNode;
struct ListNode {
   int key;
   bool counted;
   int leftEnd;
   int rightEnd;
   ListNode *next;
   ListNode *prev;
};

typedef struct IntervalTreeNode TreeNode;
struct IntervalTreeNode {
   bool color;
   int low;
   ListNode *highList;
   int listLength;
   int max;
   int min;
   TreeNode *parent;
   TreeNode *left;
   TreeNode *right;
};

struct EventListX_wrapper_structure{
   int EventListX;
   int KeyX;
};

typedef struct EventListX_wrapper_structure EventListX_wrapper;

extern TreeNode *neel;
extern TreeNode *root;
