#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"


static void DeleteFixedUpRBT( TreeNode **root, TreeNode *current )
{

   while( current != *root && current->color == BLACK )
   {
      TreeNode *sibling = NULL;

      if ( isLeftChild( current, __FILE__, __LINE__ ) )
      {
         sibling = current->parent->right;

         // Case 1: sibling is red
         if ( sibling->color == RED ){
            sibling->color = BLACK;
            sibling->parent->color = RED;
            leftRotate( sibling->parent, root );
            sibling = current->parent->right;
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 1\n");
#           endif
         }

         // Case 2: sibling is black, both children of sibling are black
         else if ( sibling->color == BLACK
           && sibling->left->color == BLACK
           && sibling->right->color == BLACK ){
            sibling->color = RED;
            current = current->parent;
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 2\n");
#           endif
         }


         // Case 3: sibling is black, right/left child of sibling is black/red
         else if ( sibling->color == BLACK
           && sibling->left->color == RED
           && sibling->right->color == BLACK ){
            sibling->color = RED;
            sibling->left->color = BLACK;
            rightRotate( sibling, root );
            sibling = current->parent->right;
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 3\n");
#           endif

         }

         // Case 4: sibling is black, right child of sibling is red
         else if ( sibling->color == BLACK
              && sibling->right->color == RED ){
            sibling->color = current->parent->color;
            current->parent->color = BLACK;
            sibling->right->color = BLACK;
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
         if ( sibling->color == RED ){
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 1-2\n");
#           endif
            sibling->color = BLACK;
            sibling->parent->color = RED;
            rightRotate( sibling->parent, root );
            sibling = current->parent->left;
         }

         // Case 2: sibling is black, both children of sibling are black
         else if ( sibling->color == BLACK
           && sibling->right->color == BLACK
           && sibling->left->color == BLACK ){
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 2-2\n");
#           endif
            sibling->color = RED;
            current = current->parent;
         }


         // Case 3: sibling is black, right/left child of sibling is black/red
         else if ( sibling->color == BLACK
           && sibling->right->color == RED
           && sibling->left->color == BLACK ){
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 3-2\n");
#           endif
            sibling->color = RED;
            sibling->right->color = BLACK;
            leftRotate( sibling, root );
            sibling = current->parent->left;

         }

         // Case 4: sibling is black, left child of sibling is red
         else if ( sibling->color == BLACK
              && sibling->left->color == RED ){
#           ifdef DEBUG
            printf("DeleteFixedUpRBT: case 4-2");
#           endif
            sibling->color = current->parent->color;
            current->parent->color = BLACK;
            sibling->left->color = BLACK;
            rightRotate( current->parent, root );
            current = *root;
         }
         else REPORT_ERROR;
      }
   }

   current->color = BLACK;

}

void DeleteNode( TreeNode **root, Interval *interval )
{

   bool deleteNodeColor = false;
   ListNode *listNode = NULL;
   TreeNode *node = SearchInterval( *root, interval, &listNode, DUPLICATE );
   TreeNode *deleteNodeChild = NULL;
   TreeNode *deleteNode      = NULL;

   if ( node == NULL ){
      printf("The interval->low %d is not found.\n", interval->low);
      return;
   }


   // Case 0: multiple high-ends in a single node
   if ( node->listLength > 1 ){
      DeleteListNode( &(node->highList), listNode );
      (node->listLength)--;
      return;
   }


   // Case 1: The node to be deleted has no child
   if ( node->left == neel && node->right == neel ){

      if ( node == *root ) { *root = neel; free(node); return;}

      if ( node->parent->left == node ){
         node->parent->left  = neel;
      }else if (node->parent->right == node){
         node->parent->right = neel;
      }else{
         REPORT_ERROR
      }

      deleteNodeColor = node->color;
      deleteNodeChild = neel;
      deleteNodeChild->parent = node->parent;
      deleteNode = node;

#     ifdef DEBUG
      printf("deleteNode: Case 1\n");
#     endif
   }

   // Case 2: The node to be deleted has left child
   else if ( node->right == neel && node->left != neel ){

      if ( node == *root ) { *root = node->left; free(node); return; }

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
   else if ( node->right != neel && node->left == neel ){

      if ( node == *root ) { *root = node->right; free(node); return; }

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
   else if ( node->right != neel && node->left != neel ){

      TreeNode *successor = inorderSuccessor(node);

      if ( successor->parent->left == successor ){
         successor->parent->left = successor->right;
      }else if( successor->parent->right == successor ){
         successor->parent->right = successor->right;
      }else{
         REPORT_ERROR
      }

      if ( successor->right != neel )
         successor->right->parent = successor->parent;

      node->low = successor->low;
      SwapPointer( (void**)&(node->highList), (void**)&(successor->highList) );

      deleteNodeColor = successor->color;
      deleteNodeChild = successor->right;
      deleteNodeChild->parent = successor->parent;
      deleteNode = successor;
   }
   else REPORT_ERROR;

   deleteNode->parent->max = max( deleteNode->parent->left->max, deleteNode->parent->right->max, deleteNode->parent->highList->key );

   // Update `max` attribute in each node on search path
   TreeNode *current = deleteNode->parent;
   while( current != *root ){
      if ( current->max > current->parent->max ) current->parent->max = current->max;
      current = current->parent;
   }


   FreeList( deleteNode->highList );
   free(deleteNode);

   if ( deleteNodeColor == BLACK )  DeleteFixedUpRBT( root, deleteNodeChild );

}

