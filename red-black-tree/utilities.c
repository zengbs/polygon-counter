#include"macro.h"
#include"rbtree.h"
#include "prototypes.h"


bool isLeftChild( TreeNode * node, char *fileName, int line )
{
   if      ( node->parent->left == node ) return true;
   else if ( node->parent->right == node ) return false;
   else { printf( "Error: %s(%d)\n", fileName, line ); exit(EXIT_FAILURE); return false; }
}

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
