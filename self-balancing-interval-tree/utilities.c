#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"


int max( int a, int b, int c )
{
   int d = MAX( a, b );
   return MAX( d, c );
}

bool isLeftChild( TreeNode * node, char *fileName, int line )
{
   if      ( node->parent->left == node ) return true;
   else if ( node->parent->right == node ) return false;
   else { printf( "Error: %s(%d)\n", fileName, line ); exit(EXIT_FAILURE); return false; }
}

TreeNode* allocateTreeNode( TreeNode **parent, Interval *interval, bool color, int left_root_right )
{
   TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

   if ( newNode == NULL ) REPORT_ERROR;

   newNode->low        = interval->low;
   newNode->highList = NULL;
   InsertListNode(&(newNode->highList), interval->high);
   newNode->listLength = 1;
   newNode->left       = neel;
   newNode->right      = neel;
   newNode->color      = color;
   newNode->max        = interval->high;

   if ( left_root_right == ROOT ){
      newNode->parent = neel;
      *parent         = newNode;
   }
   else if ( left_root_right == LEFT_CHILD ){
      newNode->parent = *parent;
      (*parent)->left = newNode;
   }else{
      newNode->parent  = *parent;
      (*parent)->right = newNode;
   }

   return newNode;
}


void printInorder( TreeNode *node ){

   if ( node == neel ) return;

   printInorder(node->left);

   printf("%d  ", node->low);

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


bool IsOverlappingIntervals( Interval *interval1, Interval *interval2 )
{
//printf("interval1->low = %d\n" , interval1->low ); // 418
//printf("interval1->high = %d\n", interval1->high); // 542
//printf("interval2->low = %d\n" , interval2->low ); // 356
//printf("interval2->high = %d\n", interval2->high); // 681
   if      ( ( interval1->low < interval2->low  ) && ( interval2->low  < interval1->high ) ) return true;
   else if ( ( interval1->low < interval2->high ) && ( interval2->high < interval1->high ) ) return true;
   else if ( ( interval2->low < interval1->low  ) && ( interval1->low  < interval2->high ) ) return true;
   else if ( ( interval2->low < interval1->high ) && ( interval1->high < interval2->high ) ) return true;
   else return false;
}

bool IsTouchingIntervals( Interval *interval1, Interval *interval2 )
{
   if ( ( interval1->high == interval2->low ) ^ ( interval2->high == interval1->low ) ) return true;
   else return false;
}


bool IsDuplicateIntervals( Interval *interval1, Interval *interval2 )
{
   if ( ( interval1->high == interval2->high ) && ( interval1->low == interval2->low ) ) return true;
   else return false;
}


bool checkTargetIntervalInNode( TreeNode *treeNode, Interval *intervalTarget, ListNode **listNode, int relativePosition )
{

   Interval intervalNode;
   intervalNode.low  = treeNode->low;
   ListNode *current = treeNode->highList;

   bool (*fptr)( Interval *interval1, Interval *interval2 );

   switch( relativePosition )
   {
      case OVERLAPPING:
         fptr = IsOverlappingIntervals;
#        ifdef DEBUG
         printf("Checking overlapping intervals..\n");
#        endif
         break;
      case TOUCHING:
         fptr = IsTouchingIntervals;
#        ifdef DEBUG
         printf("Checking touching intervals..\n");
#        endif
         break;
      case DUPLICATE:
         fptr = IsDuplicateIntervals;
#        ifdef DEBUG
         printf("Checking duplicate intervals..\n");
#        endif
         break;
      default:
         REPORT_ERROR;
   }

   while( current != NULL ){

      intervalNode.high = current->key;

      if ( fptr( intervalTarget, &intervalNode ) ){
         *listNode = current;
         PRINT_LOCATION;
         return true;
      }

      current = current->next;
   }

   return false;
}

TreeNode* SearchInterval( TreeNode *root, Interval *interval, ListNode **listNode, int relativePosition )
{
   TreeNode *current = root;

   while( current != neel ){

      if ( checkTargetIntervalInNode( current, interval, listNode, relativePosition )){
         return current;
      }else if( current->left == neel ){
         current = current->right;
      }else if( current->left->max < interval->low ){
         current = current->right;
      }else{
         current = current->left;
      }
   }


   return NULL;
}

// ====== Print the structure of tree on 2D plane =======================
// ======================================================================
#define COUNT 20

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

    if ( root != neel )
    {
       if ( root->color == BLACK )      {printf("[%d,](%d, B) ", root->low, root->max ); PrintListNode(root->highList);}
       else                             {printf("[%d,](%d, R) ", root->low, root->max ); PrintListNode(root->highList);}
    }

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D( TreeNode* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}


void SwapPointer( void **ptr1, void **ptr2 )
{
   void *temp = *ptr1;
   *ptr1 = *ptr2;
   *ptr2 = temp;
}
