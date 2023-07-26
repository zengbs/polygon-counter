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

TreeNode* allocateTreeNode( TreeNode **parent, Interval *intervalX, Interval *intervalY,
                            bool color, int left_root_right, TreeNode **root)
{
   TreeNode* newNode = (TreeNode*)malloc(sizeof(TreeNode));

   if ( newNode == NULL ) REPORT_ERROR;

   newNode->low        = intervalY->low;
   newNode->highList   = NULL;
   InsertListNode(&(newNode->highList), intervalX, intervalY);
   newNode->listLength = 1;
   newNode->left       = neel;
   newNode->right      = neel;
   newNode->color      = color;
   newNode->max        = intervalY->high;

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


void CountIntervalInNode( TreeNode *treeNode, Interval *intervalX, Interval *intervalY, ListNode **listNode,
                          int relativePosition, int *numberCounted )
{

   Interval intervalYNode, intervalXNode;
   intervalYNode.low  = treeNode->low;
   ListNode *current  = treeNode->highList;

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
         printf("Not support yet!\n");
#        endif
         break;
      case DUPLICATE:
         fptr = IsDuplicateIntervals;
#        ifdef DEBUG
         printf("Not support yet!\n");
#        endif
         break;
      default:
         REPORT_ERROR;
   }

   while( current != NULL ){

      intervalYNode.high    = current->key;
      intervalYNode.counted = current->counted;

      intervalXNode.low  = current->leftEnd;
      intervalXNode.high = current->rightEnd;

      bool overlap  = fptr( intervalY, &intervalYNode ) || IsDuplicateIntervals( intervalY, &intervalYNode );
           overlap &= fptr( intervalX, &intervalXNode ) || IsDuplicateIntervals( intervalX, &intervalXNode );


      if ( overlap && intervalY->counted == false ){
         intervalY->counted = true;
         (*numberCounted)++;
         printf("===========\n");
         printf("A: intervalY    : [%d, %d]\n", intervalY->low,       intervalY->high );
         printf("A: intervalYNode: [%d, %d]\n", intervalYNode.low,    intervalYNode.high );
         printf("A: intervalX    : [%d, %d]\n", intervalX->low,       intervalX->high );
         printf("A: intervalXNode: [%d, %d]\n", intervalXNode.low,    intervalXNode.high );
         printf("===========\n");
      }

      if ( overlap && current->counted == false ){
         current->counted = true;
         (*numberCounted)++;
         printf("===========\n");
         printf("B: intervalY    : [%d, %d]\n", intervalY->low,       intervalY->high );
         printf("B: intervalYNode: [%d, %d]\n", intervalYNode.low,    intervalYNode.high );
         printf("B: intervalX    : [%d, %d]\n", intervalX->low,       intervalX->high );
         printf("B: intervalXNode: [%d, %d]\n", intervalXNode.low,    intervalXNode.high );
         printf("===========\n");
      }

      current = current->next;
   }

}

TreeNode* CountOverlappingInterval( TreeNode *root, Interval *intervalX, Interval *intervalY,
                                    ListNode **listNode, int *numberCounted )
{
   TreeNode *current = root;


   while( current != neel ){

      CountIntervalInNode( current, intervalX, intervalY, listNode, OVERLAPPING, numberCounted );

      if( current->left == neel ){
#        ifdef DEBUG
         printf("Go to right (left = neel)\n");
#        endif
         current = current->right;
      }else if( current->left->max <= intervalY->low ){
#        ifdef DEBUG
         printf("Go to right, current->left->max=%d, current->left->low=%d, intervalY->low=%d\n", current->left->max, current->left->low, intervalY->low);
#        endif
         current = current->right;
      }else{
#        ifdef DEBUG
         printf("Go to left, current->left->max=%d, current->left->low=%d, intervalY->low=%d\n", current->left->max, current->left->low, intervalY->low);
#        endif
         current = current->left;
      }
   }


   return NULL;
}

TreeNode* SearchDuplicateInterval( TreeNode *root, Interval *interval, ListNode **listNode )
{
   TreeNode *current = root;

   int key = interval->low;

   while( current->low != key ){
      if      ( current->low > key )  current = current->left;
      else if ( current->low < key )  current = current->right;
      else { REPORT_ERROR }

      if ( current == neel ) REPORT_ERROR;
   }

   *listNode = SearchListNode( current->highList, interval->high );

   return current;
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

//    if ( root != neel )
    {
       if ( root->color == BLACK )      {printf("[%d,](%d, B) [%d] ", root->low, root->max, root->listLength ); PrintListNode(root->highList);}
       else                             {printf("[%d,](%d, R) [%d] ", root->low, root->max, root->listLength ); PrintListNode(root->highList);}
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
