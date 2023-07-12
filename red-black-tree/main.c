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
#define RED   true
#define BLACK false

typedef struct RBTNode TreeNode;

struct RBTNode {
   bool color
   int key;
   int duplicate;
   TreeNode *parent;
   TreeNode *left;
   TreeNode *right;
};


void allocateNewNode( TreeNode **parent, int key, , bool color, int left_root_right )
{
   TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

   if ( newNode == NULL ) REPORT_ERROR

   newNode->key    = key;
   newNode->left   = NULL;
   newNode->right  = NULL;
   newNode->duplicate = 1;
   newNode->color = color;

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
