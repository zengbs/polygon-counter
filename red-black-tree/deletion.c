void deleteNode( TreeNode **root, int key )
{

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
   if ( node == *root ) { *root = node->right; free(node); return; }

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

