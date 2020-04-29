//
// Created by Mor on 26/04/2020.
//

#include <memory>
#include "TreeNode.h"
#include "../MostPlayedList/ArtistPlaysNode.h"

using std::shared_ptr;
using std::make_shared;

TreeNode::TreeNode(int key) : key(key), father(nullptr), left(nullptr), right(nullptr) {
    this->height = 0;
}

TreeNode::TreeNode(int key, shared_ptr<TreeNode> father, shared_ptr<TreeNode> left, shared_ptr<TreeNode> right) {
    this->height = 0;
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

int TreeNode::GetHeight() {
    return this->height;
}

void TreeNode::SetHeight(int height) {
    this->height = height;
}

shared_ptr<TreeNode> TreeNode::GetFather() {
    return this->father;
}

shared_ptr<TreeNode> TreeNode::GetLeft() {
    return this->left;
}

shared_ptr<TreeNode> TreeNode::GetRight() {
    return this->right;
}

StatusType TreeNode::AddNode(shared_ptr<TreeNode> node) {
    return INVALID_INPUT;
}

StatusType TreeNode::RemoveNode(int key) {
    return INVALID_INPUT;
}

shared_ptr<TreeNode> TreeNode::Find(int key) {
    if (this->key == key) {
        return shared_ptr<TreeNode>(this);
    }
    shared_ptr<TreeNode> result = this->left->Find(key);
    if (result != nullptr) {
        return result;
    }
    result = this->right->Find(key);
    if (result != nullptr) {
        return result;
    }
    return nullptr;
}
