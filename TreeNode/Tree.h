//
// Created by sivan on 03/05/2020.
//

#ifndef WET1_TREE_H
#define WET1_TREE_H


//balanced AVL TREE

#include <iostream>
#include "../library1.h"

template<class T>
class TreeNode {
private:
    TreeNode();

    int key;
    T data;
    TreeNode *left;
    TreeNode *right;
    TreeNode *father;

public:
    TreeNode(int key, const T &data) : key(key), data(data), left(nullptr), right(nullptr), father(nullptr) {};

    ~TreeNode() = default;

    const T &GetData() const {
        return this->data;
    }

    void setData(T data) {
        this->data = data;
    }

    int getKey() const {
        this->key;
    }

    void setKey(int key) {
        this->key = key;
    }

    void SetLeft(TreeNode *left) {
        this->left = left;
    }

    TreeNode *GetLeft() const {
        return this->left;
    }

    void SetRight(TreeNode *right) {
        this->right = right;
    }

    TreeNode *GetRight() const {
        return this->right;
    }
    void SetFather(TreeNode *father) {
        this->fathe = father;
    }
    TreeNode* GetFather() const {
        return this->father;
    }
};

template<class T>
class Tree {
private:
    void InsertNode(TreeNode<T> *root, TreeNode<T> *ins);

    void DeleteTree(TreeNode<T> *node);

    TreeNode<T> *root;

public:
    Tree() : root(nullptr) {};

    ~Tree();

    StatusType Insert(int key, const T &value);

    TreeNode<T> *GetRoot() const { return this->root; }

    TreeNode<T> *Find(TreeNode<T> *root, int key) const;

    int Height(TreeNode<T> *root) const;

    int BalanceFactor(TreeNode<T> *root) const;

    void RotateLeft(TreeNode<T> *root);

    void RotateRight(TreeNode<T> *root);

};

template<class T>
Tree<T>::~Tree() {
    if (root) {
        DeleteTree(root);
    }
}

template<class T>
void Tree<T>::DeleteTree(TreeNode<T> *node) {
    if (node) {
        DeleteTree(node->GetLeft());
        DeleteTree(node->GetRight());
        delete node; // Post Order Deletion
    }
}

template<class T>
StatusType Tree<T>::Insert(int key, const T &value) {
    auto *new_node = new(std::nothrow) TreeNode<T>(key, value);

    if (!new_node)
        return FAILURE; // Out of memory

    if (!root) // emptyTree
        root = new_node;
    else
        InsertNode(root, new_node);

    return SUCCESS;
}

template<class T>
void Tree<T>::InsertNode(TreeNode<T> *root, TreeNode<T> *ins) {
    // Binary Search Tree insertion algorithm
    if (ins->Getkey() < root->Getkey()) {
        if (root->GetLeft()) // If there is a left child, keep searching
            InsertNode(root->GetLeft(), ins);
        else { // Found the right spot
            root->SetLeft(ins);
            ins->SetParent(root);
        }
    } else {
        if (root->GetRight()) // If there is a right child, keep searching
            InsertNode(root->GetRight(), ins);
        else {// Found the right spot
            root->SetRight(ins);
            ins->SetParent(root);
        }
    }

    // AVL balancing algorithm
    int balance = BalanceFactor(root);
    if (balance > 1) { // left tree unbalanced
        if (BalanceFactor(root->GetLeft()) < 0) // right child of left tree is the cause
            RotateLeft(root->GetLeft()); // double rotation required
        RotateRight(root);
    } else if (balance < -1) { // right tree unbalanced
        if (BalanceFactor(root->GetRight()) > 0) // left child of right tree is the cause
            RotateRight(root->GetRight());
        RotateLeft(root);
    }
}

template<class T>
TreeNode<T> *Tree<T>::Find(TreeNode<T> *root, int key) const {
    if (root) {
        if (root->GetValue() == key)
            return root; // Found
        else if (key < root->GetValue())
            return Find(root->GetLeft(), key);
        else
            return Find(root->GetRight(), key);
    }

    return nullptr;
}

template<class T>
int Tree<T>::Height(TreeNode<T> *root) const {
    int height = 0;
    if (root) {
        int left = Height(root->GetLeft());
        int right = Height(root->GetRight());
        height = 1 + ((left > right) ? left : right);
    }
    return height;
}

template<class T>
int Tree<T>::BalanceFactor(TreeNode<T> *root) const {
    int balance = 0;
    if (root) {
        balance = Height(root->GetLeft()) - Height(root->GetRight());
    }
    return balance;
    return 0;
}

template<class T>
void Tree<T>::RotateLeft(TreeNode<T> *root) {
    TreeNode <T> *newroot = root->GetRight();
    root->SetRight(newroot->GetLeft());
    newroot->SetLeft(root);

    if (root->GetParent() == nullptr) {
        root = newroot;
        newroot->SetParent(nullptr);
    } else {
        if (root->GetParent()->GetLeft() == root) {
            root->GetParent()->SetLeft(newroot);
        } else {
            root->GetParent()->SetRight(newroot);
        }
        newroot->SetParent(root->GetParent());
    }
    root->SetParent(newroot);

}

template<class T>
void Tree<T>::RotateRight(TreeNode<T> *root) {
    // Rotate node
    TreeNode <T> *newroot = root->GetLeft();
    root->SetLeft(newroot->GetRight());
    newroot->SetRight(root);

    // Adjust tree
    if (root->GetParent() == nullptr) {
        root = newroot;
        newroot->SetParent(nullptr);
    } else {
        if (root->GetParent()->GetLeft() == root) {
            root->GetParent()->SetLeft(newroot);
        } else {
            root->GetParent()->SetRight(newroot);
        }
        newroot->SetParent(root->GetParent());
    }

    root->SetParent(newroot);

}


#endif //WET1_TREE_H
