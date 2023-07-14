#include"macro.h"
#include"rbtree.h"
#include "prototypes.h"


bool isLeftChild( TreeNode * node )
{
   if      ( node->parent->left == node ) return true;
   else if ( node->parent->right == node ) return false;
   else REPORT_ERROR;
}
