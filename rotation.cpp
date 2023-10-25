#include <type_traits>
#include "includes/typedef.h"
#include "includes/global.h"
#include "includes/macro.h"
#include "includes/intervaltree.h"
#include "includes/prototypes.h"

/* ====================================================================== */
/*             A                    A                                     */
/*             |                    |                                     */
/*             x                    y                                     */
/*            / \       ==>        / \                                    */
/*           i   y                x   k                                   */
/*              / \              / \                                      */
/*             j   k            i   j                                     */
/* ====================================================================== */

template <typename T>
void leftRotate( T *x, T **root )
{
   T *y = x->right;
   T *j = y->left;
   T *A = x->parent;

   // Connect x and j
   x->right = j;
   if ( j != (T*)neel )   j->parent = x;

   // Connect A and y
   y->parent = A;

   if ( A == (T*)neel ){
      y->parent = (T*)neel;
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

   if constexpr( std::is_same<T,    IntervalTreeNode>::value )  x->max = max( x->left->max, x->right->max, x->maxKeyInSubIntervalTree );
   if constexpr( std::is_same<T,    IntervalTreeNode>::value )  x->min = min( x->left->min, x->right->min, x->key                     );

   if constexpr( std::is_same<T, SubIntervalTreeNode>::value )  x->max = max( x->left->max, x->right->max, x->key                     );

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

template <typename T>
void rightRotate( T *x, T **root )
{
   T *y = x->left;
   T *k = y->right;
   T *A = x->parent;

   // Connect x and k
   x->left = k;
   if ( k != (T*)neel )   k->parent = x;

   // Connect A and y
   y->parent = A;

   if ( A == (T*)neel ){
      y->parent = (T*)neel;
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

   if constexpr( std::is_same<T,    IntervalTreeNode>::value )  x->max = max( x->left->max, x->right->max, x->maxKeyInSubIntervalTree );
   if constexpr( std::is_same<T,    IntervalTreeNode>::value )  x->min = min( x->left->min, x->right->min, x->key                     );

   if constexpr( std::is_same<T, SubIntervalTreeNode>::value )  x->max = max( x->left->max, x->right->max, x->key                     );

}


template void rightRotate<SubIntervalTreeNode>( SubIntervalTreeNode *x, SubIntervalTreeNode **root );
template void leftRotate <SubIntervalTreeNode>( SubIntervalTreeNode *x, SubIntervalTreeNode **root );
template void rightRotate<IntervalTreeNode>( IntervalTreeNode *x, IntervalTreeNode **root );
template void leftRotate <IntervalTreeNode>( IntervalTreeNode *x, IntervalTreeNode **root );
