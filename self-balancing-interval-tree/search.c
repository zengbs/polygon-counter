#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"

TreeNode* searchNode( TreeNode *root, int leftend )
{
   TreeNode *current = root;

   while( current->leftend != leftend ){
      if      ( current->leftend > leftend )  current = current->left;
      else if ( current->leftend < leftend )  current = current->right;
      else { REPORT_ERROR }

      if ( current == NULL ) return NULL;
   }

   return current;

}
