#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"

TreeNode* searchInterval( TreeNode *root, Interval *interval )
{
   TreeNode *current = root;

   while( current->low != interval->low ){

      if      ( current->low > interval->low )  current = current->left;
      else if ( current->low < interval->low )  current = current->right;
      else    REPORT_ERROR;

      if ( current == NULL ) return NULL;
   }

   return current;
}
