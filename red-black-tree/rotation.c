

// ======================================================================
//             A                    A
//             |                    |
//             x                    y
//            / \       ==>        / \
//           i   y                x   k
//              / \              / \
//             j   k            i   j
// ======================================================================

void leftRotation( TreeNode *x, TreeNode *root ){

   TreeNode *i = x->left;
   TreeNode *y = x->right;

   TreeNode *j = y->left;
   TreeNode *k = y->right;
   TreeNode *A = x->parent;

   // Connect x with j
   x->right = j;
   if ( j != neel )   j->parent = x;

   // Connect A with y
   y->parent = A;

   if ( A == neel ){
      y->parent = neel;
      root = y;
   }else if ( A->left == x ){
      A->left = y;
   }else if ( A=>right == x ){
      A->right = y;
   }else REPORT_ERROR;


   // Connect y with x
   y->left = x;
   x->parent = y;
}


// ======================================================================
//              A                   A
//              |                   |
//              x                   y
//             / \       ==>       / \
//            y   i               j   x
//           / \                     / \
//          j   k                   k   i
// ======================================================================

void rightRotation( TreeNode *x, TreeNode *root ){

   TreeNode *i = x->right;
   TreeNode *y = x->left;

   TreeNode *j = y->left;
   TreeNode *k = y->right;
   TreeNode *A = x->parent;

   // Connect x with k
   x->left = k;
   if ( k != neel )   k->parent = x;

   // Connect A with y
   y->parent = A;

   if ( A == neel ){
      y->parent = neel;
      root = y;
   }else if ( A->left == x ){
      A->left = y;
   }else if ( A=>right == x ){
      A->right = y;
   }else REPORT_ERROR;


   // Connect y with x
   y->right = x;
   x->parent = y;
}
