bool validate(TreeNode* node, TreeNode* prev) {
    if (node == NULL) return true;
    if (!validate(node->left, prev)) return false;
    if (prev != NULL && prev->key >= node->key) return false;
    prev = node;
    return validate(node->right, prev);
}

bool isValidBST(TreeNode* root) {
    TreeNode* prev = NULL;
    return validate(root, prev);
}

