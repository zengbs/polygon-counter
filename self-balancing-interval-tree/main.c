#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"


TreeNode *neel = NULL;

TreeNode* allocateNewNode( TreeNode **parent, Interval *interval, bool color, int left_root_right )
{
   TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

   if ( newNode == NULL ) REPORT_ERROR

   newNode->low    = interval->low;
   newNode->high   = interval->high;
   newNode->left       = neel;
   newNode->right      = neel;
   newNode->duplicate  = 1;
   newNode->color      = color;

   if ( left_root_right == ROOT ){
      newNode->parent = neel;
      *parent         = newNode;
      newNode->max    = interval->high;
   }
   else if ( left_root_right == LEFT_CHILD ){
      newNode->parent = *parent;
      (*parent)->left = newNode;
      newNode->max    = interval->high;
   }else{
      newNode->parent  = *parent;
      (*parent)->right = newNode;
      newNode->max     = interval->high;
   }

   return newNode;
}


void printInorder( TreeNode *node ){

   if ( node == neel ) return;

   printInorder(node->left);

   printf("%d(%d)  ", node->low, node->duplicate);

   printInorder(node->right);

}


// Only works for the node having both child
TreeNode* inorderSuccessor( TreeNode *node ){

   TreeNode *current = node->right;

   while( current->left != neel ){
      current = current->left;
   }

   return current;
}


#define MANUAL_TEST
//#define RANDOM_TEST

int main(){

neel = (TreeNode*)malloc(sizeof(TreeNode));
neel->color = BLACK;
neel->max = INT_MIN;

TreeNode *root = neel;
root->parent = neel;

Interval interval;

#  ifdef MANUAL_TEST
   // Allocate null node
   interval.low = 4; interval.high = 5;
   InsertNode(&root, &interval);
   interval.low = 2; interval.high = 9;
   InsertNode(&root, &interval);
   interval.low = -1; interval.high = 3;
   InsertNode(&root, &interval);
   interval.low = 2; interval.high = 9;
   DeleteNode(&root, &interval);
   interval.low = -9; interval.high = 4;
   InsertNode(&root, &interval);
   interval.low = -7; interval.high = 5;
   InsertNode(&root, &interval);
   interval.low = 4; interval.high = 11;
   InsertNode(&root, &interval);
   interval.low = 7; interval.high = 9;
   InsertNode(&root, &interval);
   interval.low = -8; interval.high = 10;
   InsertNode(&root, &interval);

   print2D(root);

   if (!isValidBST(root)){
      printf("Invalid BST!\n");
      exit(EXIT_FAILURE);
   }

   if (!isBalanced(root)){
      printf("RBT is unbalanced!\n");
      exit(EXIT_FAILURE);
   }

#  endif


#  ifdef RANDOM_TEST
   // Initialization, should only be called once.
   srand((unsigned int)time(NULL));

#  define ARRAY_LENGTH 1000

   int numInsertion = 10000;
   int insert[ARRAY_LENGTH] = {0};

   for (int i=0;i<numInsertion;i++){
      // Returns a pseudo-random integer between 0 and RAND_MAX.
      int r = rand();

      InsertNode( &root, r );

      if ( insert[r%ARRAY_LENGTH] == 0)
         insert[r%ARRAY_LENGTH] = r;
      else{
         DeleteNode(&root, insert[r%ARRAY_LENGTH] );
         insert[r%ARRAY_LENGTH] = 0;
      }

      if (!isValidBST(root)){
         printf("Invalid BST! at i=%d\n", i);
         exit(EXIT_FAILURE);
      }

      if (!isBalanced(root)){
         printf("RBT is unbalanced! at i=%d\n", i);
         exit(EXIT_FAILURE);
      }
   }

#  endif

   return 0;
}