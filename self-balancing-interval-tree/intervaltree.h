#ifndef __INTERVALTREE_H___
#define __INTERVALTREE_H___


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

#endif
