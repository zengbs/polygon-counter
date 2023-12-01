#include <type_traits>
#include "../includes/typedef.h"
#include "../includes/global.h"
#include "../includes/macro.h"
#include "../includes/intervaltree.h"
#include "../includes/prototypes.h"


bool operator==(const Polygon& lhs, const Polygon& rhs){
   return lhs.polygon->size() == rhs.polygon->size() &&
          std::equal( lhs.polygon->vertices_begin(), lhs.polygon->vertices_end(), rhs.polygon->vertices_begin() );
}

template <typename T>
static void DeleteFixedUpRBT( T **root, T *current )
{

   while( current != *root && current->color == BLACK_NODE )
   {
      T *sibling = NULL;

      if ( isLeftChild( current, __FILE__, __LINE__ ) )
      {
         sibling = current->parent->right;

         // Case 1: sibling is red
         if ( sibling->color == RED_NODE ){
            sibling->color = BLACK_NODE;
            sibling->parent->color = RED_NODE;
            leftRotate( sibling->parent, root );
            sibling = current->parent->right;
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 1\n");
#           endif
         }

         // Case 2: sibling is black, both children of sibling are black
         else if ( sibling->color == BLACK_NODE
           && sibling->left->color == BLACK_NODE
           && sibling->right->color == BLACK_NODE ){
            sibling->color = RED_NODE;
            current = current->parent;
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 2\n");
#           endif
         }


         // Case 3: sibling is black, right/left child of sibling is black/red
         else if ( sibling->color == BLACK_NODE
           && sibling->left->color == RED_NODE
           && sibling->right->color == BLACK_NODE ){
            sibling->color = RED_NODE;
            sibling->left->color = BLACK_NODE;
            rightRotate( sibling, root );
            sibling = current->parent->right;
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 3\n");
#           endif

         }

         // Case 4: sibling is black, right child of sibling is red
         else if ( sibling->color == BLACK_NODE
              && sibling->right->color == RED_NODE ){
            sibling->color = current->parent->color;
            current->parent->color = BLACK_NODE;
            sibling->right->color = BLACK_NODE;
            leftRotate( current->parent, root );
            current = *root;
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 4\n");
#           endif
         }
         else REPORT_ERROR;

      }else{

         sibling = current->parent->left;
         // Case 1: sibling is red
         if ( sibling->color == RED_NODE ){
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 1-2\n");
#           endif
            sibling->color = BLACK_NODE;
            sibling->parent->color = RED_NODE;
            rightRotate( sibling->parent, root );
            sibling = current->parent->left;
         }

         // Case 2: sibling is black, both children of sibling are black
         else if ( sibling->color == BLACK_NODE
           && sibling->right->color == BLACK_NODE
           && sibling->left->color == BLACK_NODE ){
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 2-2\n");
#           endif
            sibling->color = RED_NODE;
            current = current->parent;
         }


         // Case 3: sibling is black, right/left child of sibling is black/red
         else if ( sibling->color == BLACK_NODE
           && sibling->right->color == RED_NODE
           && sibling->left->color == BLACK_NODE ){
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 3-2\n");
#           endif
            sibling->color = RED_NODE;
            sibling->right->color = BLACK_NODE;
            leftRotate( sibling, root );
            sibling = current->parent->left;

         }

         // Case 4: sibling is black, left child of sibling is red
         else if ( sibling->color == BLACK_NODE
              && sibling->left->color == RED_NODE ){
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 4-2");
#           endif
            sibling->color = current->parent->color;
            current->parent->color = BLACK_NODE;
            sibling->left->color = BLACK_NODE;
            rightRotate( current->parent, root );
            current = *root;
         }
         else REPORT_ERROR;
      }
   }

   current->color = BLACK_NODE;

}

template <typename T>
void DeleteTreeNode( T **root, Interval *intervalY, Polygon *polygon )
{

#  ifdef DEBUG
   printf("Delete [%d, %d]\n", intervalY->low, intervalY->high);
#  endif

   UINT key;
   bool deleteNodeColor = false;

   if constexpr ( std::is_same<T,    IntervalTreeNode>::value ) key = intervalY->low;
   if constexpr ( std::is_same<T, SubIntervalTreeNode>::value ) key = intervalY->high;

   T *node              = NULL;
   T *deleteNodeChild   = NULL;
   T *deleteNode        = NULL;
   T *current           = NULL;

   SearchTreeNode( *root, key, &node );

   if ( node == NULL )  REPORT_ERROR;


   // === Interval tree ===
   if constexpr ( std::is_same<T, IntervalTreeNode>::value ){

      // Case 0: multiple red-black tree nodes in an interval tree node
      if ( node->SubIntervalTreeRoot->left  != (SubIntervalTreeNode*)neel
        || node->SubIntervalTreeRoot->right != (SubIntervalTreeNode*)neel
        || node->SubIntervalTreeRoot->duplicate > 1 ){
         DeleteTreeNode(&(node->SubIntervalTreeRoot), intervalY, polygon);
#        ifdef DEBUG
         printf("DeleteTreeNode: Case 0\n");
#        endif

         // Update max/min attributes in each interval tree node on search path
         node->max = max(node->maxKeyInSubIntervalTree, node->left->max, node->right->max);
         node->min = min(node->key, node->left->min, node->right->min);
         current   = node;

         while( current != *root ){
            current->parent->max = max( current->parent->left->max, current->parent->right->max, current->parent->maxKeyInSubIntervalTree );
            current->parent->min = min( current->parent->left->min, current->parent->right->min, current->parent->key            );
            current = current->parent;
         }
         return;
      }
   }


   // === Sub interval tree ===
   if constexpr ( std::is_same<T, SubIntervalTreeNode>::value ){
      if ( node->duplicate > 1 ){
#        ifdef DEBUG
         printf("DeleteTreeNode: Case 0\n");
#        endif
         (node->duplicate)--;
         (node->counted)--;
         auto it = std::find((node->polygonsInSameBoundingBox).begin(), (node->polygonsInSameBoundingBox).end(), *polygon);
         (node->polygonsInSameBoundingBox).erase(it);
         return;
      }
   }

   // Case 1: The node to be deleted has no child
   if ( node->left == (T*)neel && node->right == (T*)neel ){
#     ifdef DEBUG
      printf("DeleteTreeNode: Case 1\n");
#     endif

      if ( node == *root ){
         if constexpr ( std::is_same<T, IntervalTreeNode>::value ){
            DeleteTreeNode(&(node->SubIntervalTreeRoot), intervalY, polygon);
            if ( node->SubIntervalTreeRoot == NULL ){
               *root = (T*)neel;
               delete node;
               node  = NULL;
            }
         }

         if constexpr ( std::is_same<T, SubIntervalTreeNode>::value ){
            (*root)->SubIntervalTreeRootParent = node->SubIntervalTreeRootParent;
            delete *root;
            *root = NULL;
         }
         return;
      }

      if ( node->parent->left == node ){
         node->parent->left  = (T*)neel;
      }else if (node->parent->right == node){
         node->parent->right = (T*)neel;
      }else{
         REPORT_ERROR
      }

      deleteNodeColor = node->color;
      deleteNodeChild = (T*)neel;
      deleteNodeChild->parent = node->parent;
      deleteNode = node;

   }

   // Case 2: The node to be deleted has left child
   else if ( node->right == (T*)neel && node->left != (T*)neel ){
#     ifdef DEBUG
      printf("DeleteTreeNode: Case 2\n");
#     endif

      if ( node == *root ){
         if constexpr ( std::is_same<T, IntervalTreeNode>::value ){
            DeleteTreeNode(&(node->SubIntervalTreeRoot), intervalY, polygon);
            if ( node->SubIntervalTreeRoot == NULL ){
               *root = node->left;
               (*root)->parent = (T*)neel;
               (*root)->color = BLACK_NODE;
               delete node;
               node = NULL;
            }
         }

         if constexpr ( std::is_same<T, SubIntervalTreeNode>::value ){
            *root = node->left;
            (*root)->parent = (T*)neel;
            (*root)->color = BLACK_NODE;
            (*root)->SubIntervalTreeRootParent = node->SubIntervalTreeRootParent;
            delete node;
            node = NULL;
         }
         return;
      }

      if ( node->parent->left == node ){
         node->parent->left  = node->left;
      }else if (node->parent->right == node){
         node->parent->right = node->left;
      }else{
         REPORT_ERROR
      }

      node->left->parent = node->parent;

      deleteNodeColor = node->color;
      deleteNodeChild = node->left;
      deleteNodeChild->parent = node->parent;
      deleteNode = node;
   }

   // Case 3: The node to be deleted has right child
   else if ( node->right != (T*)neel && node->left == (T*)neel ){
#     ifdef DEBUG
      printf("DeleteTreeNode: Case 3\n");
#     endif

      if ( node == *root ){
         if constexpr ( std::is_same<T, IntervalTreeNode>::value ){
            DeleteTreeNode(&(node->SubIntervalTreeRoot), intervalY, polygon);
            if ( node->SubIntervalTreeRoot == NULL ){
               *root = node->right;
               (*root)->parent = (T*)neel;
               (*root)->color = BLACK_NODE;
               delete node;
               node = NULL;
            }
         }

         if constexpr ( std::is_same<T, SubIntervalTreeNode>::value ){
            *root = node->right;
            (*root)->parent = (T*)neel;
            (*root)->color = BLACK_NODE;
            (*root)->SubIntervalTreeRootParent = node->SubIntervalTreeRootParent;
            delete node;
            node = NULL;
         }
         return;
      }

      if ( node->parent->left == node ){
         node->parent->left  = node->right;
      }else if (node->parent->right == node){
         node->parent->right = node->right;
      }else{
         REPORT_ERROR
      }

      node->right->parent = node->parent;

      deleteNodeColor = node->color;
      deleteNodeChild = node->right;
      deleteNodeChild->parent = node->parent;
      deleteNode = node;
   }

   // Case 4: The node to be deleted has both child
   //         --> Delete the inorder successor in right-subtree
   else if ( node->right != (T*)neel && node->left != (T*)neel ){
#     ifdef DEBUG
      printf("DeleteTreeNode: Case 4\n");
#     endif


      T *successor = inorderSuccessor(node);

      if ( successor->parent->left == successor ){
         successor->parent->left = successor->right;
      }else if( successor->parent->right == successor ){
         successor->parent->right = successor->right;
      }else{
         REPORT_ERROR
      }

      if ( successor->right != (T*)neel )
         successor->right->parent = successor->parent;

      node->key = successor->key;

      if constexpr ( std::is_same<T, IntervalTreeNode>::value ){
         SwapPointer( (void**)&(node->SubIntervalTreeRoot), (void**)&(successor->SubIntervalTreeRoot) );
         SwapPointer( (void**)&(node->SubIntervalTreeRoot->SubIntervalTreeRootParent), (void**)&(successor->SubIntervalTreeRoot->SubIntervalTreeRootParent) );
         node->maxKeyInSubIntervalTree = successor->maxKeyInSubIntervalTree;
      }

      if constexpr ( std::is_same<T, SubIntervalTreeNode>::value ){
         node->counted = successor->counted;
         node->duplicate = successor->duplicate;
         node->SubIntervalTreeRootParent = successor->SubIntervalTreeRootParent;
         // we need to copy the list from successor to the node
         std::copy(successor->polygonsInSameBoundingBox.begin(), successor->polygonsInSameBoundingBox.end(), std::back_inserter(node->polygonsInSameBoundingBox));
      }


      deleteNodeColor = successor->color;
      deleteNodeChild = successor->right;
      deleteNodeChild->parent = successor->parent;
      deleteNode = successor;
   }
   else REPORT_ERROR;


   // === Sub interval tree ===
   if constexpr ( std::is_same<T, SubIntervalTreeNode>::value ){

      // Update maxKeyInSubIntervalTree
      if ( key == (*root)->SubIntervalTreeRootParent->maxKeyInSubIntervalTree )
         (*root)->SubIntervalTreeRootParent->maxKeyInSubIntervalTree = ( node->left == (T*)neel ) ? node->parent->key : node->left->key;

      // Update max attributes in each node on search path in sub-interval tree
      deleteNode->parent->max = max( deleteNode->parent->left->max, deleteNode->parent->right->max, deleteNode->parent->key );

      current = deleteNode->parent;
      while( current != *root ){
         current->parent->max = max( current->parent->left->max, current->parent->right->max, current->parent->key );
         current = current->parent;
      }
   }

   // === Interval tree ===
   if constexpr ( std::is_same<T, IntervalTreeNode>::value ){

      // Update max/min attributes in each node on search path in interval tree
      deleteNode->parent->max = max( deleteNode->parent->left->max, deleteNode->parent->right->max, deleteNode->parent->maxKeyInSubIntervalTree );
      deleteNode->parent->min = min( deleteNode->parent->left->min, deleteNode->parent->right->min, deleteNode->parent->key            );

      current = deleteNode->parent;
      while( current != *root ){
         current->parent->max = max( current->parent->left->max, current->parent->right->max, current->parent->maxKeyInSubIntervalTree );
         current->parent->min = min( current->parent->left->min, current->parent->right->min, current->parent->key            );
         current = current->parent;
      }
   }

   if constexpr ( std::is_same<T, IntervalTreeNode>::value ){
      DeleteTreeNode(&(deleteNode->SubIntervalTreeRoot), intervalY, polygon);
      if ( deleteNode->SubIntervalTreeRoot == NULL ){
         delete deleteNode;
         deleteNode = NULL;
      }
   }

   if constexpr ( std::is_same<T, SubIntervalTreeNode>::value ){
      delete deleteNode;
      deleteNode = NULL;
   }

   if ( deleteNodeColor == BLACK_NODE )  DeleteFixedUpRBT( root, deleteNodeChild );
}



template static void DeleteFixedUpRBT<IntervalTreeNode>   ( IntervalTreeNode    **root, IntervalTreeNode    *current  );
template static void DeleteFixedUpRBT<SubIntervalTreeNode>( SubIntervalTreeNode **root, SubIntervalTreeNode *current  );
template void DeleteTreeNode<IntervalTreeNode>     ( IntervalTreeNode **root, Interval *interval, Polygon *polygon );
template void DeleteTreeNode<SubIntervalTreeNode>  ( SubIntervalTreeNode **root, Interval *interval, Polygon *polygon );
