#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<limits.h>
#include<time.h>
#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"


TreeNode *neel = NULL;



#define MANUAL_TEST
//#define RANDOM_TEST

int main(){

// Allocate neel node
neel = (TreeNode*)malloc(sizeof(TreeNode));
neel->color = BLACK;
neel->max = INT_MIN;
neel->highList = NULL;
neel->left = NULL;
neel->right = NULL;
neel->parent = NULL;

TreeNode *root = neel;

Interval interval;

#  ifdef MANUAL_TEST
   interval.low = 4; interval.high = 5;
   InsertTreeNode(&root, &interval);
   interval.low = 2; interval.high = 9;
   InsertTreeNode(&root, &interval);
   interval.low = -1; interval.high = 3;
   InsertTreeNode(&root, &interval);
   interval.low = 2; interval.high = 9;
   DeleteNode(&root, &interval);
   interval.low = -9; interval.high = 4;
   InsertTreeNode(&root, &interval);
   interval.low = -7; interval.high = 5;
   InsertTreeNode(&root, &interval);
   interval.low = 4; interval.high = 11;
   InsertTreeNode(&root, &interval);
   interval.low = 7; interval.high = 90;
   InsertTreeNode(&root, &interval);
   interval.low = -8; interval.high = 10;
   InsertTreeNode(&root, &interval);
   interval.low = -8; interval.high = 10;
   InsertTreeNode(&root, &interval);
   interval.low = -8; interval.high = 10;
   InsertTreeNode(&root, &interval);
   interval.low = -8; interval.high = 10;
   InsertTreeNode(&root, &interval);
   interval.low = -8; interval.high = 10;
   InsertTreeNode(&root, &interval);


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

      InsertTreeNode( &root, r );

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
