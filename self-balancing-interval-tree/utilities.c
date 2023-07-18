#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"


bool isLeftChild( TreeNode * node, char *fileName, int line )
{
   if      ( node->parent->left == node ) return true;
   else if ( node->parent->right == node ) return false;
   else { printf( "Error: %s(%d)\n", fileName, line ); exit(EXIT_FAILURE); return false; }
}

TreeNode* searchNode( TreeNode *root, int low )
{
   TreeNode *current = root;

   while( current->low != low ){
      if      ( current->low > low )  current = current->left;
      else if ( current->low < low )  current = current->right;
      else { REPORT_ERROR }

      if ( current == NULL ) return NULL;
   }

   return current;

}