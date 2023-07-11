
// ====== Validate the properties of binary search tree =================
// 1. The left subtree of a node contains only nodes with keys
//    less than the node's key.
// 2. The right subtree of a node contains only nodes with
//    keys greater than the node's key.
// 3. Both the left and right subtrees must also be binary search trees.
// ======================================================================
bool validateBST(TreeNode* node, TreeNode* prev) {
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

// ====== Validate the height of RB tree ================================
// ======================================================================

// ====== Validate the properties of RB tree ============================
// 1. Every node is either red or black.
// 2. All NIL nodes (figure 1) are considered black.
// 3. A red node does not have a red child.
// 4. Every path from a given node to any of its descendant NIL nodes
//    goes through the same number of black nodes.
// ======================================================================
