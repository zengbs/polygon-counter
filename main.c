# include<stdio.h>
# include<stdbool.h>
# include<stdlib.h>
# include<time.h>

#define LOCATION __FILE__, __FUNCTION__, __LINE__
#define REPORT_ERROR { printf( "Error: %s(%s):%d\n", LOCATION ); exit(EXIT_FAILURE); }
#define ROOT        0
#define LEFT_CHILD  1
#define RIGHT_CHILD 2
#define AAA 100000

typedef struct BSTNode TreeNode;

struct BSTNode {
   int key;
   int duplicate;
   TreeNode *parent;
   TreeNode *left;
   TreeNode *right;
};

# include"validate.c"

void allocateNewNode( TreeNode **parent, int key, int left_root_right )
{
   TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

   if ( newNode == NULL ) REPORT_ERROR

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


void printInorder( TreeNode *node ){

   if ( node == NULL ) return;

   printInorder(node->left);

   printf("%d(%d)  ", node->key, node->duplicate);

   printInorder(node->right);

}


// Only works for the node having both child
TreeNode* inorderSuccessor( TreeNode *node ){

   TreeNode *current = node->right;

   while( current->left != NULL ){
      current = current->left;
   }

   return current;
}

void InsertNode( TreeNode **root, int key ){

   TreeNode *current = *root;
   TreeNode *previous = NULL;
   TreeNode *newNode = NULL;

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

TreeNode* searchNode( TreeNode *root, int key )
{
   TreeNode *current = root;

   while( current->key != key ){
      if      ( current->key > key )  current = current->left;
      else if ( current->key < key )  current = current->right;
      else { REPORT_ERROR }

      if ( current == NULL ) return NULL;
   }

   return current;

}


void deleteNode( TreeNode **root, int key ){

   TreeNode *node = searchNode(*root, key);

   if ( node == NULL ){
      printf("The key %d is not found.\n", key);
      return;
   }

   // Checking duplicate
   if ( node->duplicate < 1 )  REPORT_ERROR

   // Case 0: The node to be deleted is duplicate
   if ( node->duplicate > 1 ){
      (node->duplicate)--;
      return;
   }

   // Case 1: The node to be deleted has no child
   if ( node->left == NULL && node->right == NULL ){

      if ( node == *root ) { *root = NULL; free(node); return;}

      if ( node->parent->left == node ){
         node->parent->left  = NULL;
      }else if (node->parent->right == node){
         node->parent->right = NULL;
      }else{
         REPORT_ERROR
      }

      free(node);
   }

   // Case 2: The node to be deleted has left child
   if ( node->right == NULL && node->left != NULL ){

      if ( node == *root ) { *root = node->left; free(node); return; }

      if ( node->parent->left == node ){
         node->parent->left  = node->left;
      }else if (node->parent->right == node){
         node->parent->right = node->left;
      }else{
         REPORT_ERROR
      }

      node->left->parent = node->parent;

      free(node);
   }

   // Case 3: The node to be deleted has right child
   if ( node->right != NULL && node->left == NULL ){
      if ( node->parent->left == node ){
         node->parent->left  = node->right;
      }else if (node->parent->right == node){
         node->parent->right = node->right;
      }else{
         REPORT_ERROR
      }

      node->right->parent = node->parent;

      free(node);
   }

   // Case 4: The node to be deleted has both child
   //         --> Delete the inorder successor in right-subtree
   if ( node->right != NULL && node->left != NULL ){
      TreeNode *successor = inorderSuccessor(node);

      if ( successor->parent->left == successor ){
         successor->parent->left = successor->right;
      }else if( successor->parent->right == successor ){
         successor->parent->right = successor->right;
      }else{
         REPORT_ERROR
      }

      if ( successor->right != NULL )
         successor->right->parent = successor->parent;

      node->key = successor->key;

      free(successor);
   }

}

int main(){

   // Initialization, should only be called once.
   srand((unsigned int)time(NULL));


   TreeNode *root = NULL;

   int numInsertion = 10000;

   int count = 0;


   int insert[AAA] = {0};

   for (int i=0;i<numInsertion;i++){
      // Returns a pseudo-random integer between 0 and RAND_MAX.
      int r = rand();

      InsertNode( &root, r );

      if ( insert[r%AAA] == 0)
         insert[r%AAA] = r;
      else{
         deleteNode(&root, insert[r%AAA] );
         insert[r%AAA] = 0;
      }

      if (!isValidBST(root)){
         printf("Invalid BST! at i=%d\n", i);
         exit(EXIT_FAILURE);
      }
   }


   return 0;
}
