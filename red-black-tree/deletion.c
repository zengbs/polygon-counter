void DeleteFixedUpRBT( TreeNode **root, TreeNode *current )
{

   while( current != root && current->color == BLACK )
   {
      TreeNode *sibling = NULL;

      if ( isLeftChild( current ) ) sibling = current->parent->right;
      else                          sibling = current->parent->left;

      // Case 1: sibling is red
      if ( sibling->color = RED ){

         sibling->color = BLACK;
         sibling->parent = RED;

         leftRotate( sibling->parent );
      }

      // Case 2: sibling is black, both children of sibling are black
      if ( sibling->color == BLACK
        && sibling->left->color == BLACK
        && sibling->right->color == BLACK ){

         sibling->color = RED;

         current = current->parent;

         if ( current->color = RED || current == root ) break;
      }


      // Case 3: sibling is black, right/left child of sibling is black/red
      if ( sibling->color == BLACK
        && sibling->left->color == RED
        && sibling->right->color == BLACK ){

         sibling->color = RED;
         sibling->left->color = BLACK;

         rightRotate( sibling, root );

         sibling = current->parent;

      }

      // Case 4: sibling is black, right child of sibling is red
      if ( sibling->color == BLACK
           && sibling->right->color == RED ){

         sibling->color = current->parent->color;

         current->parent->color = BLACK;

         sibling->right->color = BLACK;

         leftRotate( current->parent, root );

         current = root

      }


   }

   current->color = BLACK;

}

void deleteNode( TreeNode **root, int key )
{

   TreeNode *node = searchNode(*root, key);

   bool deleteNodeColor;
   TreeNode *deleteNodeChild = NULL;

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

      deleteNodeColor = node->color;
      deleteNodeChild->parent = node->parent;

      free(node);
   }

   // Case 2: The node to be deleted has left child
   else if ( node->right == NULL && node->left != NULL ){

      if ( node == *root ) { *root = node->left; free(node); return; }

      if ( node->parent->left == node ){
         node->parent->left  = node->left;
      }else if (node->parent->right == node){
         node->parent->right = node->left;
      }else{
         REPORT_ERROR
      }

      node->left->parent = node->parent;

      deleteNodeColor = node->color;
      deleteNodeChild = node->left;
      deleteNodeChild->parent = node->parent;

      free(node);
   }

   // Case 3: The node to be deleted has right child
   else if ( node->right != NULL && node->left == NULL ){

      if ( node == *root ) { *root = node->right; free(node); return; }

      if ( node->parent->left == node ){
         node->parent->left  = node->right;
      }else if (node->parent->right == node){
         node->parent->right = node->right;
      }else{
         REPORT_ERROR
      }

      node->right->parent = node->parent;

      deleteNodeColor = node->color;
      deleteNodeChild = node->right;
      deleteNodeChild->parent = node->parent;

      free(node);
   }

   // Case 4: The node to be deleted has both child
   //         --> Delete the inorder successor in right-subtree
   else if ( node->right != NULL && node->left != NULL ){

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

      deleteNodeColor = successor->color;
      deleteNodeChild = successor->right;
      deleteNodeChild->parent = successor->parent;

      free(successor);
   }
   else REPORT_ERROR;


   if ( deleteNodeColor == BLACK )  DeleteFixedUpRBT( root, deleteNodeChild );

}

