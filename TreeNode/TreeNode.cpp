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

StatusType TreeNode::AddNode(const shared_ptr<TreeNode>& node) {
    //adding the node
    if (this->GetRight()== nullptr && this->GetLeft()== nullptr) {
        //check if should add at right
        if (this->GetKey() < node->GetKey()) {
            this->right = node;
            node->SetFather(shared_ptr<TreeNode>(this));
        }
        //check if should add at left
        else if (this->GetKey() > node->GetKey()) {
            this->left = node;
            node->SetFather(shared_ptr<TreeNode>(this));
        }
        //they both have the same key
        else{
            return FAILURE;
        }
        node->SetHeight(1+max(node->left->GetHeight(), node->right->GetHeight()));

        //get BF
        int balance = GetBalance(node);

        //check which rotate we should perform if this node is not balanced

        //LL case
        if(balance>1 && (node->GetKey() < node->left->GetKey())){
            if(!RightRotate(node)){
                return ALLOCATION_ERROR;
            }
        }

        //RR case
        if(balance<-1 && (node->GetKey() > node->right->GetKey())){
            if(!LeftRotate(node)){
                return ALLOCATION_ERROR;
            }
        }

        //LR case
        if(balance>1 && (node->GetKey() > node->left->GetKey())){
            if(!LeftRotate(node->GetLeft())){
                return ALLOCATION_ERROR;
            }
            if(!RightRotate(node)){
                return ALLOCATION_ERROR;
            }
        }

        //RL case
        if(balance<-1 && (node->GetKey() < node->right->GetKey())){
            if(!RightRotate(node->GetRight())){
                return ALLOCATION_ERROR;
            }
            if(!LeftRotate(node)){
                return ALLOCATION_ERROR;
            }
        }
        return SUCCESS;
    }

    //need to add this node in the left side of the tree
    if (this->GetKey() > node->GetKey()) {
         return this->GetLeft()->AddNode(node);
    }
        //need to add this node in the right side of the tree
    else if (this->GetKey() < node->GetKey()) {
        return this->GetRight()->AddNode(node);
    }
        //equal keys are not allowed
    else {
        return FAILURE;
    }

}

StatusType TreeNode::RemoveNode(int key) {
    //there isn't any node with a matching key in the tree
    if (this->GetRight() == nullptr && this->GetLeft() == nullptr && this->GetKey()!= key) {
        return FAILURE;
    }
    //searching for element
    if (this->GetKey() > key) {
        return this->GetLeft()->RemoveNode(key);
    }
    else if (this->GetKey() < key) {
        return this->GetRight()->RemoveNode(key);
    }
    //found a matching key, should remove this node
    else {
        //with one child or zero
        if (this->GetRight() == nullptr || this->GetLeft() == nullptr) {
            shared_ptr<TreeNode>(temp) = (this->GetRight() ? this->GetLeft() : this->GetRight());
            //no child case
            if (temp == nullptr){
                temp = shared_ptr<TreeNode>(this);
                shared_ptr<TreeNode>(this).reset();
            }
            // one child case
            else{
                shared_ptr<TreeNode>(this) = temp; //copy the contents of the non empty child
                shared_ptr<TreeNode>(temp).reset();
            }

        }
        //with two children case
        else{
            shared_ptr<TreeNode>(temp) = FindMin(shared_ptr<TreeNode>(this->GetRight()));
            this->SetKey(temp->GetKey()); //Copy the inorder successor's data to this node
            this->GetRight()->RemoveNode(temp->GetKey()); //Delete the inorder successor
        }

        //update the height of the current node
        this->SetHeight(1+max(this->GetLeft()->height,this->GetRight()->height));

        //get the BF of this node
        int balance = GetBalance(shared_ptr<TreeNode>(this));

        //in case this node is not balanced, there are 4 cases

        //LL rotate case
        if (balance>1 && GetBalance(this->GetLeft())>=0) {
            if(!RightRotate(shared_ptr<TreeNode>(this))) {
                return ALLOCATION_ERROR; // ????
            }
        }

        //LR case
        if (balance>1 && GetBalance(this->left)<0) {
            if(!LeftRotate(this->left)){
                return ALLOCATION_ERROR;
            }
            if(!RightRotate(shared_ptr<TreeNode>(this))){
                return ALLOCATION_ERROR;
            }
        }

        //RR case
        if (balance<-1 && GetBalance(this->right)<=0) {
            if (!LeftRotate(shared_ptr<TreeNode>(this))){
                return ALLOCATION_ERROR;
            }
        }

        //RL case
        if(balance<-1 && GetBalance(this->right)>0) {
            if(!RightRotate(this->right)){
                return ALLOCATION_ERROR;
            }
            if(!LeftRotate(shared_ptr<TreeNode>(this))){
                return ALLOCATION_ERROR;
            }
        }

    }
    return SUCCESS;
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

int TreeNode::max(int a, int b) {
    return (a > b ? a : b);
}

int TreeNode::CalcHeight(const shared_ptr<TreeNode>& node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

void TreeNode::SetFather(shared_ptr<TreeNode> newFather) {
    this->father = std::move(newFather);
}

int TreeNode::GetBalance(const shared_ptr<TreeNode>& node) {
    if (node == nullptr)
        return 0;
    return (node->GetLeft())->height - (node->GetRight()->height);
}

shared_ptr<TreeNode> TreeNode::FindMax(shared_ptr<TreeNode> node) {
    if(node == nullptr)
        return nullptr;
    else if(node->GetLeft() == nullptr)
        return node;
    else
        return FindMin(node->GetLeft());
}

shared_ptr<TreeNode> TreeNode::FindMin(shared_ptr<TreeNode> node) {
    if(node == nullptr)
        return nullptr;
    else if(node->GetRight() == nullptr)
        return node;
    else
        return FindMax(node->GetRight());
}

shared_ptr<TreeNode> TreeNode::LeftRotate(const shared_ptr<TreeNode>& node) {
    shared_ptr<TreeNode> nodeRight = node->GetRight();
    shared_ptr<TreeNode> LeftOfRight = nodeRight->GetLeft();

    //perform rotation
    nodeRight->left = node;
    node->right = LeftOfRight;

    //update heights
    node->SetHeight(max(node->left->GetHeight(), node->right->GetHeight())+1);
    nodeRight->SetHeight(max(nodeRight->left->GetHeight(),
            nodeRight->right->GetHeight())+1);

    //return new root
    return nodeRight;
}

shared_ptr<TreeNode> TreeNode::RightRotate(const shared_ptr<TreeNode>& node) {

    shared_ptr<TreeNode> nodeLeft = node->GetLeft();
    shared_ptr<TreeNode> RightOfLeft = nodeLeft->GetRight();

     //perform rotation
     nodeLeft->right = node;
     node->left = RightOfLeft;

     //update heights
     node->SetHeight(max(node->left->GetHeight(), node->right->GetHeight())+1);
     nodeLeft->SetHeight(max(nodeLeft->left->GetHeight(),
             nodeLeft->right->GetHeight())+1);
     //return new root
    return nodeLeft;
}