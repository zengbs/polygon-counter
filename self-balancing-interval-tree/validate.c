#include<stdbool.h>
#include<stdlib.h>
#include"macro.h"
#include"intervaltree.h"
#include"prototypes.h"

// ====== Validate the properties of binary search tree =================
// 1. The left subtree of a node contains only nodes with leftends
//    less than the node's leftend.
// 2. The right subtree of a node contains only nodes with
//    leftends greater than the node's leftend.
// 3. Both the left and right subtrees must also be binary search trees.
// ======================================================================
bool validateBST(TreeNode* node, TreeNode* prev) {
    if (node == neel) return true;
    if (!validateBST(node->left, prev)) return false;
    if (prev != neel && prev->leftend >= node->leftend) return false;
    prev = node;
    return validateBST(node->right, prev);
}

bool isValidBST(TreeNode* root) {
    TreeNode* prev = neel;
    return validateBST(root, prev);
}

// ====== Validate the height of RB tree ================================
// Returns true if the Binary tree is balanced like a Red-Black tree.
// This function also sets value in maxh and minh (passed by reference).
// maxh and minh are set as maximum and minimum heights of root.
// ======================================================================
bool isBalancedUtil(TreeNode *root, int *maxh, int *minh)
{
    // Base case
    if (root == NULL)
    {
        *maxh = *minh = 0;
        return true;
    }

    int lmxh, lmnh; // To store max and min heights of left subtree
    int rmxh, rmnh; // To store max and min heights of right subtree

    // Check if left subtree is balanced, also set lmxh and lmnh
    if (isBalancedUtil(root->left, &lmxh, &lmnh) == false)
        return false;

    // Check if right subtree is balanced, also set rmxh and rmnh
    if (isBalancedUtil(root->right, &rmxh, &rmnh) == false)
        return false;

    // Set the max and min heights of this node for the parent call
    *maxh = MAX(lmxh, rmxh) + 1;
    *minh = MIN(lmnh, rmnh) + 1;

    // See if this node is balanced
    if (*maxh <= 2*(*minh))
        return true;

    return false;
}

// A wrapper over isBalancedUtil()
bool isBalanced(TreeNode *root)
{
    int maxh, minh;
    return isBalancedUtil(root, &maxh, &minh);
}
// ====== Validate the properties of RB tree ============================
// 1. Every node is either red or black.
// 2. All NIL nodes (figure 1) are considered black.
// 3. A red node does not have a red child.
// 4. Every path from a given node to any of its descendant NIL nodes
//    goes through the same number of black nodes.
// ======================================================================


// ====== Print the structure of tree on 2D plane =======================
// ======================================================================
#define COUNT 12

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

    if ( root->color == BLACK )      printf("%d(B)\n", root->leftend);
    else                             printf("%d(R)\n", root->leftend);

    // Process left child
    print2DUtil(root->left, space);
}

// Wrapper over print2DUtil()
void print2D( TreeNode* root)
{
    // Pass initial space count as 0
    print2DUtil(root, 0);
}
