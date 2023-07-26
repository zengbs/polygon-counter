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

void InsertTreeNode( TreeNode **root, Interval *intervalX, Interval *intervalY )
{

   if ( intervalY->low >= intervalY->high ) REPORT_ERROR;
   if ( intervalX->low >= intervalX->high ) REPORT_ERROR;

   TreeNode *current = *root;
   TreeNode *previous = neel;

   while( current != neel ){

      previous = current;

      if ( current->low > intervalY->low ){
         current = current->left;
      }else if ( current->low < intervalY->low ){
         current = current->right;
      }else{
         InsertListNode(&(current->highList), intervalX, intervalY );
         (current->listLength)++;
         current->max = current->highList->key;
         return;
      }

   }

   TreeNode *newNode = NULL;


   if ( previous == neel )
      newNode = allocateTreeNode( root     , intervalX, intervalY, BLACK, ROOT        , root);
   else if ( previous->low > intervalY->low )
      newNode = allocateTreeNode( &previous, intervalX, intervalY, RED,   LEFT_CHILD  , root);
   else
      newNode = allocateTreeNode( &previous, intervalX, intervalY, RED,   RIGHT_CHILD , root);


   // Update `max` attribute in each node on search path
   current = newNode;
   while( current != *root ){
      if ( current->max > current->parent->max ) current->parent->max = current->max;
      current = current->parent;
   }


   // Fix up RB tree
   InsertTreeNodeFixUpRBTree( root, newNode );

}
