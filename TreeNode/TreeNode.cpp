//
// Created by Mor on 26/04/2020.
//

#include "TreeNode.h"

TreeNode::TreeNode(int key) : key(key), father(nullptr), left(nullptr), right(nullptr) {

}

TreeNode::TreeNode(int key, TreeNode *father, TreeNode *left, TreeNode *right) {
    this->key = key;
    this->father = father;
    this->left = left;
    this->right = right;
}

int TreeNode::GetKey() {
    return this->key;
}

void TreeNode::SetKey(int key) {
    this->key = key;
}

TreeNode *TreeNode::GetFather() {
    return this->father;
}

TreeNode *TreeNode::GetLeft() {
    return this->left;
}

TreeNode *TreeNode::GetRight() {
    return this->right;
}

StatusType TreeNode::AddNode(TreeNode *node) {
    return INVALID_INPUT;
}

StatusType TreeNode::RemoveNode(int key) {
    return INVALID_INPUT;
}

TreeNode *TreeNode::Find(int key) {
    if (this->key == key) {
        return this;
    }
    TreeNode *result = this->left->Find(key);
    if (result != nullptr) {
        return result;
    }
    result = this->right->Find(key);
    if (result != nullptr) {
        return result;
    }
    return nullptr;
}
