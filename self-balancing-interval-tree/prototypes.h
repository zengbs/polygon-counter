void rightRotate( TreeNode *x, TreeNode **root );
void  leftRotate( TreeNode *x, TreeNode **root );
void InsertTreeNode( TreeNode **root, Interval *interval );
void DeleteTreeNode( TreeNode **root, Interval *interval );
TreeNode* allocateTreeNode( TreeNode **parent, Interval *interval, bool color, int left_root_right );
void printInorder( TreeNode *node );
TreeNode* inorderSuccessor( TreeNode *node );
bool validateBST(TreeNode* node, TreeNode* prev);
bool isValidBST(TreeNode* root);
bool isBalanced(TreeNode *root);
void print2D( TreeNode* root);
bool isLeftChild( TreeNode * node, char *fileName, int line );
ListNode *SearchListNode( ListNode *head, int key );
void InsertListNode( ListNode **head, Interval *interval );
void DeleteListNode( ListNode **head, ListNode *deleteNode );
void PrintListNode( ListNode *head );
void FreeList( ListNode *head );
bool IsOverlappingIntervals( Interval *interval1, Interval *interval2 );
bool IsTouchingIntervals( Interval *interval1, Interval *interval2 );
bool IsTargetIntervalOverlapsIntervalsInNode( TreeNode *treeNode, Interval *intervalTarget, ListNode **listNode );
void SweepLine( int *EventListX, int *EventListY, int numRectangles, int *counter );
void SwapPointer( void **ptr1, void **ptr2 );
int max( int a, int b, int c );
void RectanglesGeneration(
int numberRectanglesMax, int *numberRectangles,
int boxSizeX, int boxSizeY,
int rectangularMaxSizeX, int rectangularMaxSizeY,
int rectangularMinSizeX, int rectangularMinSizeY,
int **EventListX, int **EventListY );
TreeNode* SearchInterval( TreeNode *root, Interval *interval, ListNode **listNode,
                          int relativePosition, int mode, int *numberCounted );
