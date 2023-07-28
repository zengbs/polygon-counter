#include"macro.h"
#include"intervaltree.h"
#include "prototypes.h"


static void InsertTreeNodeFixUpRBTree( TreeNode **root, TreeNode *newNode )
{
   TreeNode *current = newNode;

   while ( current->parent->color == RED ){

      if ( current->parent->parent->left == current->parent ){

         TreeNode *uncle = current->parent->parent->right;

         // Case 1: uncle is red, current is left/right child
         if ( uncle->color == RED ){

#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 1-0\n");
#           endif

            // Step 1: paint parent black
            current->parent->color = BLACK;

            // Step 2: paint uncle black
            uncle->color = BLACK;

            // Step 3: paint grand parent red
            current->parent->parent->color = RED;

            // Step 4: move current to its grandparent
            current = current->parent->parent;
         }

         // Case 2: uncle is black, current is left child
         else if ( uncle->color == BLACK && current->parent->left == current ){
#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 2-0\n");
#           endif


            // Step 1: paint parent black
            current->parent->color = BLACK;

            // Step 2: paint grand parent red
            current->parent->parent->color = RED;

            // Step 3: right rotate based on grandparent
            rightRotate( current->parent->parent, root );
         }

         // Case 3: uncle is black, current is right child
         else if ( uncle->color == BLACK && current->parent->right == current ){

#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 3-0\n");
#           endif

            // Step 1: move current to parent
            current = current->parent;


            // Step 2: left rotate based on current
            leftRotate( current, root );


            // Repeat case 2:
            // Step 1: paint parent black
            current->parent->color = BLACK;

            // Step 2: paint grand parent red
            current->parent->parent->color = RED;

            // Step 3: right rotate based on grandparent
            rightRotate( current->parent->parent, root );

         }
         else REPORT_ERROR;


      }
      else if ( current->parent->parent->right == current->parent ){

         TreeNode *uncle = current->parent->parent->left;

         // Case 1: uncle is red, current is right/left child
         if ( uncle->color == RED ){

#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 1-1\n");
#           endif

            // Step 1: paint parent black
            current->parent ->color = BLACK;

            // Step 2: paint uncle black
            uncle->color = BLACK;

            // Step 3: paint grand parent red
            current->parent->parent->color = RED;

            // Step 4: move current to its grandparent
            current = current->parent->parent;
         }

         // Case 2: uncle is black, current is left child
         else if ( uncle->color == BLACK && current->parent->right == current ){

#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 2-1\n");
#           endif

            // Step 1: paint parent black
            current->parent->color = BLACK;

            // Step 2: paint grand parent red
            current->parent->parent->color = RED;

            // Step 3: right rotate based on grandparent
            leftRotate( current->parent->parent, root );
         }

         // Case 3: uncle is black, current is right child
         else if ( uncle->color == BLACK && current->parent->left == current ){

#           ifdef DEBUG
            printf("InsertTreeNodeFixUpRBTree case 3-1\n");
#           endif

            // Step 1: move current to parent
            current = current->parent;

            // Step 2: left rotate based on current
            rightRotate( current, root );

            // Repeat case 2:
            // Step 1: paint parent black
            current->parent->color = BLACK;

            // Step 2: paint grand parent red
            current->parent->parent->color = RED;

            // Step 3: right rotate based on grandparent
            leftRotate( current->parent->parent, root );
         }else REPORT_ERROR

      }else REPORT_ERROR

   }

   (*root)->color = BLACK;

}

void InsertTreeNode( TreeNode **root, Interval *intervalY )
{

   if ( intervalY->low >= intervalY->high ) REPORT_ERROR;

   TreeNode *current = *root;
   TreeNode *previous = neel;

   while( current != neel ){

      previous = current;

      if ( current->low > intervalY->low ){
         current = current->left;
      }else if ( current->low < intervalY->low ){
         current = current->right;
      }else{
         InsertListNode(&(current->highList), intervalY );
         (current->listLength)++;

         // Update max/min attributes in each node on search path
         current->max = max(current->highList->key, current->left->max, current->right->max );
         current->min = min(current->low, current->left->min, current->right->min );
         while( current != *root ){
            current->parent->max = max( current->parent->left->max, current->parent->right->max, current->parent->highList->key );
            current->parent->min = min( current->parent->left->min, current->parent->right->min, current->parent->low );
            current = current->parent;
         }

         return;
      }

   }

   TreeNode *newNode = NULL;


   if ( previous == neel )
      newNode = allocateTreeNode( root     , intervalY, BLACK, ROOT        , root);
   else if ( previous->low > intervalY->low )
      newNode = allocateTreeNode( &previous, intervalY, RED,   LEFT_CHILD  , root);
   else
      newNode = allocateTreeNode( &previous, intervalY, RED,   RIGHT_CHILD , root);


   // Update max/min attributes in each node on search path
   current = newNode;
   current->max = max( current->left->max, current->right->max, current->highList->key );
   current->min = min( current->left->min, current->right->min, current->low );

   while( current != *root ){
      current->parent->max = max( current->parent->left->max, current->parent->right->max, current->parent->highList->key );
      current->parent->min = min( current->parent->left->min, current->parent->right->min, current->parent->low           );
      current = current->parent;
   }


   // Fix up RB tree
   InsertTreeNodeFixUpRBTree( root, newNode );

}
