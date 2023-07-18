#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"


bool isLeftChild( TreeNode * node, char *fileName, int line )
{
   if      ( node->parent->left == node ) return true;
   else if ( node->parent->right == node ) return false;
   else { printf( "Error: %s(%d)\n", fileName, line ); exit(EXIT_FAILURE); return false; }
}

TreeNode* allocateNewNode( TreeNode **parent, Interval *interval, bool color, int left_root_right )
{
   TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

   if ( newNode == NULL ) REPORT_ERROR

   newNode->low    = interval->low;
   newNode->high   = interval->high;
   newNode->left       = neel;
   newNode->right      = neel;
   newNode->duplicate  = 1;
   newNode->color      = color;

   if ( left_root_right == ROOT ){
      newNode->parent = neel;
      *parent         = newNode;
      newNode->max    = interval->high;
   }
   else if ( left_root_right == LEFT_CHILD ){
      newNode->parent = *parent;
      (*parent)->left = newNode;
      newNode->max    = interval->high;
   }else{
      newNode->parent  = *parent;
      (*parent)->right = newNode;
      newNode->max     = interval->high;
   }

   return newNode;
}


void printInorder( TreeNode *node ){

   if ( node == neel ) return;

   printInorder(node->left);

   printf("%d(%d)  ", node->low, node->duplicate);

   printInorder(node->right);

}


// Only works for the node having both child
TreeNode* inorderSuccessor( TreeNode *node ){

   TreeNode *current = node->right;

   while( current->left != neel ){
      current = current->left;
   }

   return current;
}


TreeNode* searchInterval( TreeNode *root, Interval *interval )
{
   TreeNode *current = root;

   while( current->low != interval->low ){

      if      ( current->low > interval->low )  current = current->left;
      else if ( current->low < interval->low )  current = current->right;
      else    REPORT_ERROR;

      if ( current == NULL ) return NULL;
   }

   return current;
}

// ====== Print the structure of tree on 2D plane =======================
// ======================================================================
#define COUNT 12

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(TreeNode* root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->right, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");

    if ( root->color == BLACK )      printf("[%d,%d](%d, B)\n", root->low, root->high, root->max);
    else                             printf("[%d,%d](%d, R)\n", root->low, root->high, root->max);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D( TreeNode* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}
