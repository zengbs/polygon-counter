#include <stdbool.h>
#include <stdlib.h>
#include "../includes/global.h"
#include "../includes/macro.h"
#include "../includes/intervaltree.h"
#include "../includes/prototypes.h"

// ====== Validate the properties of binary search tree =================
// 1. The left subtree of a node contains only nodes with keys less than the node's key.
// 2. The right subtree of a node contains only nodes with keys greater than the node's key.
// 3. Both the left and right subtrees must also be binary search trees.
// ======================================================================
template <typename T>
bool validateBST(T* node, T* prev) {
    if (node == (T*)neel) return true;
    if (!validateBST(node->left, prev)) return false;
    if (prev != (T*)neel && prev->key >= node->key) return false;
    prev = node;
    return validateBST(node->right, prev);
}

template <typename T>
bool isValidBST(T* root) {
    T* prev = (T*)neel;
    return validateBST(root, prev);
}

// ====== Validate the height of RB tree ================================
// Returns true if the Binary tree is balanced like a Red-Black tree.
// This function also sets value in maxh and minh (passed by reference).
// maxh and minh are set as maximum and minimum heights of root.
// ======================================================================
template <typename T>
bool isBalancedUtil(T *root, UINT *maxh, UINT *minh)
{
    // Base case
    if (root == NULL)
    {
        *maxh = *minh = 0;
        return true;
    }

    UINT lmxh, lmnh; // To store max and min heights of left subtree
    UINT rmxh, rmnh; // To store max and min heights of right subtree

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
template <typename T>
bool isBalanced(T *root)
{
    UINT maxh, minh;
    return isBalancedUtil(root, &maxh, &minh);
}
// ====== Validate the properties of RB tree ============================
// 1. Every node is either red or black.
// 2. All NIL nodes (figure 1) are considered black.
// 3. A red node does not have a red child.
// 4. Every path from a given node to any of its descendant NIL nodes
//    goes through the same number of black nodes.
// ======================================================================

template bool validateBST(IntervalTreeNode* node, IntervalTreeNode* prev);
template bool validateBST(SubIntervalTreeNode* node, SubIntervalTreeNode* prev);
template bool isValidBST(IntervalTreeNode* root);
template bool isValidBST(SubIntervalTreeNode* root);
template bool isBalancedUtil(IntervalTreeNode *root, UINT *maxh, UINT *minh);
template bool isBalancedUtil(SubIntervalTreeNode *root, UINT *maxh, UINT *minh);
template bool isBalanced(IntervalTreeNode *root);
template bool isBalanced(SubIntervalTreeNode *root);
