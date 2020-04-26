//
// Created by Mor on 26/04/2020.
//

#include "TreeNode.h"
#include "library1.h"

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
