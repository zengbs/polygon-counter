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

   TreeNode *root = NULL;

   InsertNode(&root, 2);
   InsertNode(&root, 3);
   InsertNode(&root, 4);
   InsertNode(&root, 5);
   InsertNode(&root, 6);
   InsertNode(&root, 7);
   InsertNode(&root, 8);
   InsertNode(&root, 9);
   InsertNode(&root, 10);
   InsertNode(&root, 11);

   return 0;
}
