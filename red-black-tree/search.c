#include"macro.h"
#include"rbtree.h"
#include "prototypes.h"

TreeNode* searchNode( TreeNode *root, int key )
{
   TreeNode *current = root;

   while( current->key != key ){
      if      ( current->key > key )  current = current->left;
      else if ( current->key < key )  current = current->right;
      else { REPORT_ERROR }

      if ( current == NULL ) return NULL;
   }

   return current;

}
