# include<stdio.h>
# include<stdlib.h>

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

void inorderSuccessor( node *node ){

   if ( node->left == NULL ){
      printf("%d(%d)  ", node->key, node->duplicate);
      return;
   }

   inorderSuccessor(node->left);
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
      else { printf("Something wrong at %d\n", __LINE__); }

      if ( current == NULL ) return NULL;
   }

   return current;

}


void deleteNode( node **root, int key ){

   // Case 1: The node to be deleted has no child

   // Case 2: The node to be deleted has either left or right child

   // Case 3: The node to be deleted has both child


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


   node *node = searchNode(root, 2);

   printf("%d\n", node->key);

   //printInorder(root);

   //inorderSuccessor(root);

   return 0;
}
