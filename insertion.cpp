#include <type_traits>
#include "includes/typedef.h"
#include "includes/global.h"
#include "includes/macro.h"
#include "includes/intervaltree.h"
#include "includes/prototypes.h"


template <typename T>
static void InsertTreeNodeFixUpRBTree( T **root, T *newNode )
{

   T *current = newNode;

   while ( current->parent->color == RED_NODE ){

      if ( current->parent->parent->left == current->parent ){

         T *uncle = current->parent->parent->right;

         // Case 1: uncle is red, current is left/right child
         if ( uncle->color == RED_NODE ){

#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 1-0\n");
#           endif

            // Step 1: paint parent black
            current->parent->color = BLACK_NODE;

            // Step 2: paint uncle black
            uncle->color = BLACK_NODE;

            // Step 3: paint grand parent red
            current->parent->parent->color = RED_NODE;

            // Step 4: move current to its grandparent
            current = current->parent->parent;
         }

         // Case 2: uncle is black, current is left child
         else if ( uncle->color == BLACK_NODE && current->parent->left == current ){
#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 2-0\n");
#           endif


            // Step 1: paint parent black
            current->parent->color = BLACK_NODE;

            // Step 2: paint grand parent red
            current->parent->parent->color = RED_NODE;

            // Step 3: right rotate based on grandparent
            rightRotate( current->parent->parent, root );
         }

         // Case 3: uncle is black, current is right child
         else if ( uncle->color == BLACK_NODE && current->parent->right == current ){

#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 3-0\n");
#           endif

            // Step 1: move current to parent
            current = current->parent;


            // Step 2: left rotate based on current
            leftRotate( current, root );


            // Repeat case 2:
            // Step 1: paint parent black
            current->parent->color = BLACK_NODE;

            // Step 2: paint grand parent red
            current->parent->parent->color = RED_NODE;

            // Step 3: right rotate based on grandparent
            rightRotate( current->parent->parent, root );

         }
         else REPORT_ERROR;


      }
      else if ( current->parent->parent->right == current->parent ){

         T *uncle = current->parent->parent->left;

         // Case 1: uncle is red, current is right/left child
         if ( uncle->color == RED_NODE ){

#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 1-1\n");
#           endif

            // Step 1: paint parent black
            current->parent ->color = BLACK_NODE;

            // Step 2: paint uncle black
            uncle->color = BLACK_NODE;

            // Step 3: paint grand parent red
            current->parent->parent->color = RED_NODE;

            // Step 4: move current to its grandparent
            current = current->parent->parent;
         }

         // Case 2: uncle is black, current is left child
         else if ( uncle->color == BLACK_NODE && current->parent->right == current ){

#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 2-1\n");
#           endif

            // Step 1: paint parent black
            current->parent->color = BLACK_NODE;

            // Step 2: paint grand parent red
            current->parent->parent->color = RED_NODE;

            // Step 3: right rotate based on grandparent
            leftRotate( current->parent->parent, root );
         }

         // Case 3: uncle is black, current is right child
         else if ( uncle->color == BLACK_NODE && current->parent->left == current ){

#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 3-1\n");
#           endif

            // Step 1: move current to parent
            current = current->parent;

            // Step 2: left rotate based on current
            rightRotate( current, root );

            // Repeat case 2:
            // Step 1: paint parent black
            current->parent->color = BLACK_NODE;

            // Step 2: paint grand parent red
            current->parent->parent->color = RED_NODE;

            // Step 3: right rotate based on grandparent
            leftRotate( current->parent->parent, root );
         }else REPORT_ERROR

      }else REPORT_ERROR

   }

   (*root)->color = BLACK_NODE;

}


template <typename T>
void InsertTreeNode( T **root, Interval *intervalY, Polygon* polygon, IntervalTreeNode *SubIntervalTreeRootParent )
{

   T *current = *root;
   T *previous = (T*)neel;

   UINT key;

   if constexpr( std::is_same<T,    IntervalTreeNode>::value ) key = intervalY->low;
   if constexpr( std::is_same<T, SubIntervalTreeNode>::value ) key = intervalY->high;

   while( current != (T*)neel ){

      if (current == NULL) REPORT_ERROR;

      previous = current;

      if ( current->key > key ){
#        ifdef DEBUG
         printf("Case 1\n");
#        endif
         current = current->left;
      }else if ( current->key < key ){
#        ifdef DEBUG
         printf("Case 2\n");
#        endif
         current = current->right;
      }else{
#        ifdef DEBUG
         printf("Case 3\n");
#        endif
         // === Interval tree ===
         if constexpr( std::is_same<T, IntervalTreeNode>::value ){

            // Insert high-end of intervalY into red-black tree
            InsertTreeNode( &(current->SubIntervalTreeRoot), intervalY, polygon, current );

            // [OPTIMIZE] No need to update maxKeyInSubIntervalTree and max attributes when there is a duplicate node in sub interval tree

            // Update the maxKeyInSubIntervalTree in interval tree
            current->maxKeyInSubIntervalTree = MAX( current->maxKeyInSubIntervalTree, intervalY->high );

            // Update max attributes in each node on search path
            current->max = max(current->maxKeyInSubIntervalTree, current->left->max, current->right->max );
            current->min = min(current->key                    , current->left->min, current->right->min );

            while( current != *root ){
               current->parent->max = max( current->parent->left->max, current->parent->right->max, current->parent->maxKeyInSubIntervalTree );
               current->parent->min = min( current->parent->left->min, current->parent->right->min, current->parent->key                     );
               current = current->parent;
            }
         }

         // === Sub interval tree ===
         if constexpr( std::is_same<T, SubIntervalTreeNode>::value ){
            (current->duplicate)++;
            (current->polygonsInSameBoundingBox).push_back(*polygon);
         }

         return;

      } // if ( current->key > key )

   } //while( current != neel )

   T *newNode = NULL;

   if ( previous == (T*)neel ){
      newNode = allocateTreeNode( root     , intervalY, BLACK_NODE, ROOT_NODE  );
   }else if ( previous->key > key ){
      newNode = allocateTreeNode( &previous, intervalY, RED_NODE  , LEFT_CHILD );
   }else{
      newNode = allocateTreeNode( &previous, intervalY, RED_NODE  , RIGHT_CHILD);
   }


   if constexpr( std::is_same<T, SubIntervalTreeNode>::value ){
      newNode->SubIntervalTreeRootParent = SubIntervalTreeRootParent;
      (newNode->polygonsInSameBoundingBox).push_back(*polygon);
   }

   current = newNode;

   // === Interval tree ===
   if constexpr( std::is_same<T, IntervalTreeNode>::value ){


      // Insert high-end of intervalY into red-black tree
      InsertTreeNode( &(newNode->SubIntervalTreeRoot), intervalY, polygon, newNode );


      // Update max/min attributes in each node on search path
      current->max = max( current->left->max, current->right->max, current->maxKeyInSubIntervalTree );
      current->min = min( current->left->min, current->right->min, current->key                     );

      while( current != *root ){
         current->parent->max = max( current->parent->left->max, current->parent->right->max, current->parent->maxKeyInSubIntervalTree );
         current->parent->min = min( current->parent->left->min, current->parent->right->min, current->parent->key                     );
         current = current->parent;
      }
   }


   // === Sub interval tree ===
   if constexpr( std::is_same<T, SubIntervalTreeNode>::value ){

      // Update max attributes in each node on search path
      current->max = max( current->left->max, current->right->max, current->key );

      while( current != *root ){
         current->parent->max = max( current->parent->left->max, current->parent->right->max, current->parent->key );
         current = current->parent;
      }
   }

   // Fix up RB-based interval tree
   InsertTreeNodeFixUpRBTree( root, newNode );

}


template static void InsertTreeNodeFixUpRBTree<IntervalTreeNode>( IntervalTreeNode **root, IntervalTreeNode *newNode );
template static void InsertTreeNodeFixUpRBTree<SubIntervalTreeNode>( SubIntervalTreeNode **root, SubIntervalTreeNode *newNode );
template void InsertTreeNode<IntervalTreeNode>( IntervalTreeNode **root, Interval *intervalY, Polygon* polygon, IntervalTreeNode *SubIntervalTreeRootParent );
template void InsertTreeNode<SubIntervalTreeNode>( SubIntervalTreeNode **root, Interval *intervalY, Polygon* polygon, IntervalTreeNode *SubIntervalTreeRootParent );
