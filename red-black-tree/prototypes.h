void rightRotate( TreeNode *x, TreeNode *root );
void  leftRotate( TreeNode *x, TreeNode *root );
void InsertNodeFixUpRBT( TreeNode *root, TreeNode *newNode );
TreeNode* allocateNewNode( TreeNode **parent, int key, bool color, int left_root_right );
void printInorder( TreeNode *node );
TreeNode* inorderSuccessor( TreeNode *node );
