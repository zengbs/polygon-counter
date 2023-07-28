#include"macro.h"
#include"intervaltree.h"
#include "prototypes.h"

/* ====================================================================== */
/*             A                    A                                     */
/*             |                    |                                     */
/*             x                    y                                     */
/*            / \       ==>        / \                                    */
/*           i   y                x   k                                   */
/*              / \              / \                                      */
/*             j   k            i   j                                     */
/* ====================================================================== */

void leftRotate( TreeNode *x, TreeNode **root )
{
   TreeNode *y = x->right;
   TreeNode *j = y->left;
   TreeNode *A = x->parent;

   // Connect x and j
   x->right = j;
   if ( j != neel )   j->parent = x;

   // Connect A and y
   y->parent = A;

   if ( A == neel ){
      y->parent = neel;
      *root = y;
   }else if ( A->left == x ){
      A->left = y;
   }else if ( A->right == x ){
      A->right = y;
   }else REPORT_ERROR;


   // Connect y and x
   y->left = x;
   x->parent = y;

   // Update max/min attributes
   y->max = x->max;
   y->min = x->min;
   x->max = max( x->left->max, x->right->max, x->highList->key );
   x->min = min( x->left->min, x->right->min, x->low           );

}


/* ====================================================================== */
/*              A                   A                                     */
/*              |                   |                                     */
/*              x                   y                                     */
/*             / \       ==>       / \                                    */
/*            y   i               j   x                                   */
/*           / \                     / \                                  */
/*          j   k                   k   i                                 */
/* ====================================================================== */

void rightRotate( TreeNode *x, TreeNode **root )
{
   TreeNode *y = x->left;
   TreeNode *k = y->right;
   TreeNode *A = x->parent;

   // Connect x and k
   x->left = k;
   if ( k != neel )   k->parent = x;

   // Connect A and y
   y->parent = A;

   if ( A == neel ){
      y->parent = neel;
      *root = y;
   }else if ( A->left == x ){
      A->left = y;
   }else if ( A->right == x ){
      A->right = y;
   }else REPORT_ERROR;


   // Connect y and x
   y->right = x;
   x->parent = y;


   // Update max/min attributes
   y->max = x->max;
   y->min = x->min;
   x->max = max( x->left->max, x->right->max, x->highList->key );
   x->min = min( x->left->min, x->right->min, x->low           );

}
