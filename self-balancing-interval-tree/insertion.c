#include"macro.h"
#include"intervaltree.h"
#include "prototypes.h"


static void InsertNodeFixUpIntervalTree( TreeNode **root, TreeNode *newNode )
{
   TreeNode *current = newNode;

   while ( current->parent->color == RED ){

      if ( current->parent->parent->left == current->parent ){

         TreeNode *uncle = current->parent->parent->right;

         // Case 1: uncle is red, current is left/right child
         if ( uncle->color == RED ){

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

            // Step 1: paint parent black
            current->parent->color = BLACK;

            // Step 2: paint grand parent red
            current->parent->parent->color = RED;

            // Step 3: right rotate based on grandparent
            rightRotate( current->parent->parent, root );
         }

         // Case 3: uncle is black, current is right child
         else if ( uncle->color == BLACK && current->parent->right == current ){

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

            // Step 1: paint parent black
            current->parent->color = BLACK;

            // Step 2: paint grand parent red
            current->parent->parent->color = RED;

            // Step 3: right rotate based on grandparent
            leftRotate( current->parent->parent, root );
         }

         // Case 3: uncle is black, current is right child
         else if ( uncle->color == BLACK && current->parent->left == current ){

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

void InsertNode( TreeNode **root, Interval *interval )
{

   if ( interval->low > interval->high ) REPORT_ERROR;

   TreeNode *current = *root;
   TreeNode *previous = neel;

   while( current != neel ){

      previous = current;

      if ( current->low > interval->low ){
         current = current->left;
      }else if ( current->low < interval->low ){
         current = current->right;
      }else{
         (current->duplicate)++;
         return;
      }

   }

   TreeNode *newNode = NULL;

   if ( previous == neel )
      newNode = allocateNewNode( root     , interval, BLACK, ROOT        );
   else if ( previous->low > interval->low )
      newNode = allocateNewNode( &previous, interval, RED,   LEFT_CHILD  );
   else
      newNode = allocateNewNode( &previous, interval, RED,   RIGHT_CHILD );


   // Update `max` attribute in each node on search path
   current = newNode;
   while( current != *root ){
      if ( current->max > current->parent->max ) current->parent->max = current->max;
      current = current->parent;
   }


   // Fix up RB tree
   InsertNodeFixUpIntervalTree( root, newNode );

}
