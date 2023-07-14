#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>
#include<time.h>
#include"macro.h"
#include"rbtree.h"
#include "prototypes.h"


TreeNode *neel = NULL;

TreeNode* allocateNewNode( TreeNode **parent, int key, bool color, int left_root_right )
{
   TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

   if ( newNode == NULL ) REPORT_ERROR

   newNode->key    = key;
   newNode->left   = neel;
   newNode->right  = neel;
   newNode->duplicate = 1;
   newNode->color = color;

   if ( left_root_right == ROOT ){
      newNode->parent = neel;
      *parent = newNode;
   }
   else if ( left_root_right == LEFT_CHILD ){
      newNode->parent = *parent;
      (*parent)->left  = newNode;
   }else{
      newNode->parent = *parent;
      (*parent)->right = newNode;
   }

   return newNode;
}


void printInorder( TreeNode *node ){

   if ( node == neel ) return;

   printInorder(node->left);

   printf("%d(%d)  ", node->key, node->duplicate);

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



int main(){

   // Allocate null node
   neel = (TreeNode*)malloc(sizeof(TreeNode));
   neel->color = BLACK;

   TreeNode *root = neel;
   root->parent = neel;

   InsertNode(&root, -2);
   InsertNode(&root, -3);
   InsertNode(&root, -4);
   InsertNode(&root, -5);
   InsertNode(&root, -6);
   InsertNode(&root, -7);
   InsertNode(&root, -8);
   InsertNode(&root, -9);
   InsertNode(&root, -10);
   InsertNode(&root, -11);
   InsertNode(&root, -12);
   InsertNode(&root, -13);
   InsertNode(&root, -14);
   InsertNode(&root, -15);
   InsertNode(&root, -16);
   InsertNode(&root, -17);
   InsertNode(&root, -18);
   InsertNode(&root, -19);

   print2D(root);

   if (!isBalanced(root)){
      printf("RBT is unbalanced!\n");
      exit(EXIT_FAILURE);
   }
//   // Initialization, should only be called once.
//   srand((unsigned int)time(NULL));
//
//
//
//   int numInsertion = 10000;
//
//   //int count = 0;
//
//
//   //int insert[AAA] = {0};
//
//   for (int i=0;i<numInsertion;i++){
//
//      int r = rand();
//
//      InsertNode( &root, r );
//
//      if (!isValidBST(root)){
//         printf("Invalid BST! at i=%d\n", i);
//         exit(EXIT_FAILURE);
//      }
//
//      if (!isBalanced(root)){
//         printf("RBT is unbalanced! at i=%d\n", i);
//         exit(EXIT_FAILURE);
//      }
//
//   }

   return 0;
}
