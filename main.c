# include<stdio.h>
# include<stdlib.h>
# include<stdbool.h>

#define ROOT        0
#define LEFT_CHILD  1
#define RIGHT_CHILD 2

typedef struct BSTNode node;

struct BSTNode {
   int key;
   int duplicate;
   node *parent;
   node *left;
   node *right;
};


void allocateNewNode( node **parent, int key, int left_root_right )
{
   node* newNode = (node*)malloc(sizeof(node));

   newNode->key    = key;
   newNode->left   = NULL;
   newNode->right  = NULL;
   newNode->duplicate = 1;

   if ( left_root_right == ROOT ){
      newNode->parent = NULL;
      *parent = newNode;
   }
   else if ( left_root_right == LEFT_CHILD ){
      newNode->parent = *parent;
      (*parent)->left  = newNode;
   }else{
      newNode->parent = *parent;
      (*parent)->right = newNode;
   }
}


void printInorder( node *node ){

   if ( node == NULL ) return;

   printInorder(node->left);

   printf("%d(%d)  ", node->key, node->duplicate);

   printInorder(node->right);

}


// Only works for the node having both child
node* inorderSuccessor( node *targetNode ){

   node *current = targetNode;

   while( current->left == NULL && current->right != NULL ){
      current = current->right;
   }

   while( current->left != NULL ){
      current = current->left;
   }

   return current;
}

void InsertNode( node **root, int key ){

   node *current = *root;
   node *previous = NULL;
   node *newNode = NULL;

   while( current != NULL ){

      previous = current;

      if ( current->key > key ){
         current = current->left;
      }else if ( current->key < key ){
         current = current->right;
      }else{
         (current->duplicate)++;
         return;
      }

   }

   if ( previous == NULL )           allocateNewNode( root, key, ROOT );
   else if ( previous->key > key )   allocateNewNode( &previous, key, LEFT_CHILD );
   else                              allocateNewNode( &previous, key, RIGHT_CHILD );
}

node* searchNode( node *root, int key )
{
   node *current = root;

   while( current->key != key ){
      if      ( current->key > key )  current = current->left;
      else if ( current->key < key )  current = current->right;
      else { printf("Something wrong at %d\n", __LINE__); exit(1); }

      if ( current == NULL ) return NULL;
   }

   return current;

}


void deleteNode( node **root, int key ){

   node *targetNode = searchNode(*root, key);

   if ( targetNode == NULL ){
      printf("The key %d is not found.\n", key);
      return;
   }

   // Checking duplicate
   if ( targetNode->duplicate < 1 ){
      printf("Node duplicate is less than 1\n", targetNode->duplicate);
      exit(1);
   }

   // Case 0: The node to be deleted is duplicate
   if ( targetNode->duplicate > 1 ){
      (targetNode->duplicate)--;
      return;
   }

   // Case 1: The node to be deleted has no child
   if ( targetNode->left == NULL && targetNode->right == NULL ){
      if ( targetNode->parent->left == targetNode ){
         targetNode->parent->left  = NULL;
      }else{
         targetNode->parent->right = NULL;
      }

      free(targetNode);
   }

   // Case 2: The node to be deleted has left child
   if ( targetNode->right == NULL && targetNode->left != NULL ){
      if ( targetNode->parent->left == targetNode ){
         targetNode->parent->left  = targetNode->left;
      }else{
         targetNode->parent->right = targetNode->left;
      }

      free(targetNode);
   }

   // Case 3: The node to be deleted has right child
   if ( targetNode->right != NULL && targetNode->left == NULL ){
      if ( targetNode->parent->left == targetNode ){
         targetNode->parent->left  = targetNode->right;
      }else{
         targetNode->parent->right = targetNode->right;
      }

      free(targetNode);
   }

   // Case 4: The node to be deleted has both child
   //         --> Delete the inorder successor in right-subtree
   if ( targetNode->right != NULL && targetNode->left != NULL ){

      node *successor = inorderSuccessor(targetNode);

        // Since successor is always left child of its parent
        // we can safely make successor's right child as left of its parent.
        // If there is no succ, then assign succ->right to succParent->right
      if ( successor->parent != *root )
         successor->parent->left = successor->right;
      else
         successor->parent->right = successor->right;

      targetNode->key = successor->key;

      free(successor);
   }

}

int main(){

   node *root = NULL;

   InsertNode( &root, 2 );
   InsertNode( &root, -6 );
   InsertNode( &root, 6 );
   InsertNode( &root, 3 );
   InsertNode( &root, 10 );
   InsertNode( &root, 5 );
   InsertNode( &root, 1 );
   InsertNode( &root, -3 );
   InsertNode( &root, 10 );
   InsertNode( &root, 10 );
   InsertNode( &root, -10 );
   InsertNode( &root, 10 );
   InsertNode( &root, 6 );





   printInorder(root);

   deleteNode(&root, 6);
   deleteNode(&root, 6);
   printf("\n");
   printInorder(root);

   return 0;
}
