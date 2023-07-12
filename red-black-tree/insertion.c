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

