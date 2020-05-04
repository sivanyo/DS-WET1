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

    TreeNode *GetFather() const {
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

    StatusType RemoveNode(TreeNode<T>, int key);

    TreeNode<T> FindMax(TreeNode<T> node);

    TreeNode<T> FindMin(TreeNode<T> node);

    TreeNode<T> GetNextNode(const TreeNode<T> &node)
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
    TreeNode<T> *newroot = root->GetRight();
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
    TreeNode<T> *newRoot = root->GetLeft();
    root->SetLeft(newRoot->GetRight());
    newRoot->SetRight(root);

    // Adjust tree
    if (root->GetParent() == nullptr) {
        root = newRoot;
        newRoot->SetParent(nullptr);
    } else {
        if (root->GetParent()->GetLeft() == root) {
            root->GetParent()->SetLeft(newRoot);
        } else {
            root->GetParent()->SetRight(newRoot);
        }
        newRoot->SetParent(root->GetParent());
    }

    root->SetParent(newRoot);

}

template<class T>
StatusType Tree<T>::RemoveNode(TreeNode<T> root, int key) {
    //no matching key
    if (root.getKey() != key && root.GetRight() == nullptr && root.GetLeft() == nullptr) {
        return FAILURE;
    }

    if (key < root.getKey()) {
        root->left = deleteNode(root->left, key);
    } else if (key > root.getKey()) {
        root->right = deleteNode(root->right, key);
    }

        // if key is same as root's key, then This is the node to be deleted
    else {
        // node with only one child or no child
        if ((root->left == nullptr) || (root->right == nullptr)) {
            TreeNode<T> *temp = (root->left ? root->left : root->right);
            // No child case
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else// One child case
                *root = *temp; // Copy the contents of the non-empty child
            delete temp;
        } else {
            // node with two children: Get the inorder
            // successor (smallest in the right subtree)
            TreeNode<T> *temp = FindMin(root.GetRight());

            // Copy the inorder successor's data to this node
            root.setKey(temp->getKey());
            root.setData(temp->GetData());

            // Delete the inorder successor
            root->right = deleteNode(root->right, temp->key);
        }
    }

    //update heights
    root->height = 1 + max(height(root->left),
                           height(root->right));

    //get BF
    int balance = getBalance(root);

    // If this node becomes unbalanced, then there are 4 cases
    // LL Case
    if (balance > 1 &&
        getBalance(root->left) >= 0)
        return rightRotate(root);

    // LR Case
    if (balance > 1 &&
        getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // RR Case
    if (balance < -1 &&
        getBalance(root->right) <= 0)
        return leftRotate(root);

    // RL Case
    if (balance < -1 &&
        getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    return SUCCESS;
}

template<class T>
TreeNode<T> Tree<T>::FindMax(TreeNode<T> node) {
    if (node == nullptr)
        return nullptr;
    else if (node->GetLeft() == nullptr)
        return node;
    else
        return FindMin(node->GetLeft());
}

template<class T>
TreeNode<T> Tree<T>::FindMin(TreeNode<T> node) {
    if (node == nullptr)
        return nullptr;
    else if (node->GetRight() == nullptr)
        return node;
    else
        return FindMax(node->GetRight());
}

template<class T>
TreeNode<T> Tree<T>::GetNextNode(const TreeNode<T> &node) {
    if (node->right == nullptr) {
        return FindMin(node->right);
    } else {
        TreeNode<T> parent = node->GetFather();
        while (parent != nullptr) {
            if (parent->left == node) {
                break;
            }
            node = parent;
            parent = node->father;
        }
        return parent;
    }
}


#endif //WET1_TREE_H
