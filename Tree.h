//
// Created by sivan on 03/05/2020.
//

#ifndef WET1_TREE_H
#define WET1_TREE_H

#include <iostream>
#include <algorithm>
#include "library1.h"
#include <iostream> // TODO only for testing
/**
 * Generic Template Class for a TreeNode
 * Made Specifically for use as a balanced AVL tree node meant to store dynamic
 * user data
 */
template<class T>
class TreeNode {
private:
    int key;
    T *data;
    int height;
    TreeNode<T> *left;
    TreeNode<T> *right;
    TreeNode<T> *parent;

    TreeNode<T> *Rebalance();

    int getBalanceFactor();

    void SwapNodesParent(TreeNode<T> *takePlace);

    void updateNodeHeight();

    TreeNode<T> *DeleteAndReplaceNodeWithLeftSuccessor();

    TreeNode<T> *DeleteAndReplaceNodeWithRightSuccessor();

    TreeNode<T> *LeftRightRotate();

    TreeNode<T> *RightLeftRotatet();

    TreeNode<T> *LeftRotate();

    TreeNode<T> *RightRotate();

    TreeNode<T> *DeleteNode(int keyRemove);

public:
    TreeNode(int key, T *nData = nullptr, TreeNode *parent = nullptr);

    ~TreeNode();

    void DeleteTreeData();

    TreeNode<T> *Insert(int keyAdd, T *dataAdd = nullptr, TreeNode<T> *result = nullptr);

    TreeNode<T> *Remove(int keyRemove);

    TreeNode<T> *Find(int keyFind);

    TreeNode<T> *findMin();

    TreeNode<T> *findMax();

    T *getData();

    TreeNode<T> *getNext();

    int getKey();

    TreeNode<T> *getLeft();

    void setLeft(TreeNode<T> *ptr);

    TreeNode<T> *getRight();

    void setRight(TreeNode<T> *ptr);

    TreeNode<T> *getParent();

    void setParent(TreeNode<T> *ptr);

    int mapInOrder(int *keys, int size);

    int mapSucc(int *keys, int size);

    void removeDataPointer();

    int getNodeBalanceFactor();

    TreeNode<T> *DeleteNode();
};

/**
 * Creates a new TreeNode for insertion to an AVL tree
 * Provided key is a dynamically allocated data of type T
 * @tparam T Pointer to dynamically allocated object of type T
 * @param key A key
 * @param nData
 * @param parent
 */
template<class T>
TreeNode<T>::TreeNode(int key, T *nData, TreeNode *parent):
        key(key), data(nData), height(1), left(nullptr), right(nullptr), parent(parent) {};

/**
 * delete the node and all its sons, grandsons and so on
 * use when we want to delete not just the current node (this) but all the data that connects to it
 * @param T
 */
template<class T>
void TreeNode<T>::DeleteTreeData() {
    if (left != nullptr) {
        left->DeleteTreeData();
        delete left;
        left = nullptr;
    }
    if (right != nullptr) {
        right->DeleteTreeData();
        delete right;
        right = nullptr;
    }
}

/**
 * @tparam T
 * @return the custom data of the node
 */
template<class T>
T *TreeNode<T>::getData() {
    return data;
}

/**
 * @tparam T
 * @return node's key
 */
template<class T>
int TreeNode<T>::getKey() {
    return key;
}


/**
 *
 * @tparam T
 * @param keyAdd
 * @param dataAdd
 * @return add a new node in this connected nodes data structure, with param keyAdd and dataAdd
 * the Insert is by AVL-ordering-by-key
 * if during Insert founds that keyAdd already in struct, does not do anything
 */
template<class T>
TreeNode<T> *TreeNode<T>::Insert(int keyAdd, T *dataAdd, TreeNode<T> *result) {

    if (keyAdd > key) {
        if (right == nullptr) {
            right = new TreeNode(keyAdd, dataAdd, this);
            result = right;
        } else {
            right->Insert(keyAdd, dataAdd, result);
        }
    } else if (keyAdd < key) {
        if (left == nullptr) {
            left = new TreeNode(keyAdd, dataAdd, this);
            result = left;
        } else {
            left->Insert(keyAdd, dataAdd, result);
        }
    } else {
        return nullptr; // indicate already in tree. no actions or changing in tree
    }
    return Rebalance();
}

/**
 * updeate node's height
 * @tparam T
 */
template<class T>
void TreeNode<T>::updateNodeHeight() {
    int tmpRight = 0, tmpLeft = 0;
    if (left != nullptr) {
        tmpLeft = left->height;
    }
    if (right != nullptr) {
        tmpRight = right->height;
    }

    if (tmpLeft > tmpRight) {
        height = tmpLeft + 1;
    } else {
        height = tmpRight + 1;
    }
}

/**
 * single right rotation
 * @tparam T
 * @return update root of sub-node-struct
 */
template<class T>
TreeNode<T> *TreeNode<T>::RightRotate() {
    TreeNode<T> *tmpRight = right;
    right = right->left;
    if (right != nullptr) {
        right->parent = this;
    }
    tmpRight->left = this;
    tmpRight->parent = this->parent;
    if (this->parent != nullptr) {
        if (this->parent->left != nullptr && this->parent->left->key == this->key) {
            this->parent->left = tmpRight;
        } else {
            this->parent->right = tmpRight;
        }
    }
    this->parent = tmpRight;
    this->updateNodeHeight();
    tmpRight->updateNodeHeight();
    return tmpRight;
}

/**
 * single left rotation
 * @tparam T
 * @return update root of sub-node-struct
 */
template<class T>
TreeNode<T> *TreeNode<T>::LeftRotate() {
    TreeNode<T> *tmpLeft = left;
    left = left->right;
    if (left != nullptr) {
        left->parent = this;
    }
    tmpLeft->right = this;
    tmpLeft->parent = this->parent;
    if (this->parent != nullptr) {
        if (this->parent->left != nullptr && this->parent->left->key == this->key) {
            this->parent->left = tmpLeft;
        } else {
            this->parent->right = tmpLeft;
        }
    }
    this->parent = tmpLeft;
    this->updateNodeHeight();
    tmpLeft->updateNodeHeight();
    return tmpLeft;
}

/**
 * one right rotation and than left rotation
 * @tparam T
 * @return update root of sub-node-struct
 */
template<class T>
TreeNode<T> *TreeNode<T>::LeftRightRotate() {
    left->RightRotate();
    return this->LeftRotate();
}

/**
 * one left rotation and than right rotation
 * @tparam T
 * @return update root of sub-node-struct
 */
template<class T>
TreeNode<T> *TreeNode<T>::RightLeftRotatet() {
    right->LeftRotate();
    return this->RightRotate();
}

template<class T>
int TreeNode<T>::getBalanceFactor() {
    updateNodeHeight();
    int tmpRight = 0, tmpLeft = 0;
    if (right != nullptr) {
        tmpRight = right->height;
    }
    if (left != nullptr) {
        tmpLeft = left->height;
    }
    return tmpLeft - tmpRight;
}

/**
 * balances nodes (as AVL tree)
 * @tparam T
 * @return update root of sub-node-struct
 */
template<class T>
TreeNode<T> *TreeNode<T>::Rebalance() {
    int bf = getBalanceFactor(); // bf = Balance Factor

    if (bf > 1) {
        int sub_bf = left->getBalanceFactor();
        if (sub_bf >= 0) {
            return LeftRotate();
        } else {
            return LeftRightRotate();
        }
    } else if (bf < -1) {
        int sub_bf = right->getBalanceFactor();
        if (sub_bf > 0) {
            return RightLeftRotatet();
        } else {
            return RightRotate();
        }
    }
    return this;
}

/**
 * delete this (Current) from node-struct
 * @tparam T
 * @param keyRemove
 * @return update root of sub-node-struct
 */
template<class T>
TreeNode<T> *TreeNode<T>::DeleteNode(int keyRemove) {
    if (left != nullptr) { //Find successor of node
        TreeNode<T> *successor = left->findMax();
        if (left->right != nullptr) {
            successor->parent->right = successor->left;
            if (successor->left != nullptr) {
                successor->left->parent = successor->parent;
            }
            successor->left = this->left;
            this->left->parent = successor;
        }
        this->SwapNodesParent(successor);
        successor->right = this->right;
        if (this->right != nullptr) {
            this->right->parent = successor;
        }
        delete this;
        return successor->Rebalance();
    } else if (right != nullptr) {
        TreeNode<T> *successor = this->right;
        this->SwapNodesParent(successor);
        delete this;
        return successor->Rebalance();
    } else { // no sons to delete node
        this->SwapNodesParent(nullptr);
        delete this;
        return nullptr;
    }
}

/**
 * adjust parents between nodes that been delete and its successor
 * @tparam T
 * @param takePlace - successor
 */
template<class T>
void TreeNode<T>::SwapNodesParent(TreeNode<T> *takePlace) {
    if (takePlace != nullptr) {
        takePlace->parent = this->parent;
    }
    if (this->parent != nullptr) {
        if (this->parent->left != nullptr && this->parent->left->key == this->key) {
            this->parent->left = takePlace;
        } else {
            this->parent->right = takePlace;
        }
    }
}

/**
 * scan the node-struct by "in-order" method
 * (from current down. does not go up to parent)
 * @tparam T
 * @param keys - arr. assign the  #size lowest keys in the tree into this arr
 * @param size - num of data to copy into keys[]
 * @return the number of keys that were assign to keys[]
 */
template<class T>
int TreeNode<T>::mapInOrder(int *keys, int size) {
    if (size <= 0 || keys == nullptr) {
        return 0;
    }

    int index = 0;
    if (left != nullptr) {
        index += left->mapInOrder(keys, size);
        if (index >= size) {
            return index;
        }
    }

    keys[index++] = key;

    if (index < size && right != nullptr) {
        index += right->mapInOrder(keys + index, size - index);
    }
    return index;
}

/**
 * scan the node-struct by "successor in-order" method
 * (from current up. does not go to current sons)
 * @tparam T
 * @param keys - arr. assign the  #size lowest keys in the tree into this arr
 * @param size - num of data to copy into keys[]
 * @return the number of keys that were assign to keys[]
 */
template<class T>
int TreeNode<T>::mapSucc(int *keys, int size) {
    if (size <= 0 || keys == nullptr) {
        return 0;
    }
    int index = 0;
    TreeNode<T> *current = this;
    while (current && index < size) {
        keys[index++] = current->key;
        if (current->right) {
            index += current->right->mapInOrder(keys + index, size - index);
        }
        current = current->parent;
    }
    return index;
}

/**
 * Replaces a node that is targeted for delete with it's leftmost successor
 * @tparam T Pointer to dynamically allocated object of type T
 * @return The new root of the node's subtree after it's removal
 */
template<class T>
TreeNode<T> *TreeNode<T>::DeleteAndReplaceNodeWithLeftSuccessor() {
    TreeNode<T> *next = left->findMax();
    if (left->getRight()) {
        next->parent->right = next->left;
        if (next->getLeft()) {
            next->left->parent = next->parent;
        }
        // might need to be reversed
        this->left->parent = next;
        next->left = this->left;
    }
    // Performing pointer and parent swap between the next node and the
    // node we need to delete
    this->SwapNodesParent(next);
    next->right = this->right;
    if (this->getRight()) {
        this->right->parent = next;
    }
    delete this;
    return next->Rebalance();
}

/**
 * Replaces a node that is targeted for delete with it's right successor
 * @tparam T Pointer to dynamically allocated object of type T
 * @return The new root of the node's subtree after it's removal
 */
template<class T>
TreeNode<T> *TreeNode<T>::DeleteAndReplaceNodeWithRightSuccessor() {
    TreeNode<T> *next = this->right;
    // Performing pointer and parent swap between the next node and the
    // node we need to delete
    this->SwapNodesParent(next);
    delete this;
    return next->Rebalance();
}

template<class T>
TreeNode<T> *TreeNode<T>::getNext() {
    TreeNode<T> *current = this;
    if (current->getRight() != nullptr) {
        // This node has a right child, which means if we follow the branch
        // once to the right and then all the way to the left, we will find the
        // correct following child
        TreeNode<T> *rightOfCurrent = current->getRight();
        return rightOfCurrent->findMin();
    } else {
        TreeNode<T> *parent = current->getParent();
        while (parent != nullptr) {
            TreeNode<T> *child = parent->getLeft();
            if (child && child->getKey() == current->getKey()) {
                // The node we started with is the left child of the current parent,
                // which means the parent is the next node in the tree.
                return parent;
            }
            current = parent;
            parent = current->getParent();
        }
        return parent;
    }
}

/**
 * Returns the balance factor of the node
 * @tparam T Pointer to dynamically allocated object of type T
 * @return The balance factor of the tree node
 */
template<class T>
int TreeNode<T>::getNodeBalanceFactor() {
    return getBalanceFactor();
}

/**
 * Deletes the data stored in this node,
 * marks the data as deleted and deletes the node itself
 * (does not delete child nodes)
 * @tparam T Pointer to dynamically allocated object of type T
 */
template<class T>
TreeNode<T>::~TreeNode() {
    if (data) {
        delete data;
        data = nullptr;
    }
}

/**
 * Searches for a tree node with the input key and returns a pointer to it
 * @tparam T Pointer to dynamically allocated object of type T
 * @param searchKey The key of the node to search for
 * @return A pointer to the tree node if it is found, nullptr otherwise
 */
template<class T>
TreeNode<T> *TreeNode<T>::Find(int searchKey) {
    if (getKey() > searchKey) {
        // The node we are looking for is a left child of this node
        if (left) {
            return left->Find(searchKey);
        } else {
            return nullptr;
        }
    } else if (getKey() < searchKey) {
        // The node we are looking for is a right child of this node
        if (right) {
            return right->Find(searchKey);
        } else {
            return nullptr;
        }
    } else {
        // We found the node we were looking for
        return this;
    }
}

/**
 * Removes a node with input key from the tree
 * @tparam T Pointer to dynamically allocated object of type T
 * @param nodeKey The key of the node to remove
 * @return The new root of the subtree after removal of the node
 */
template<class T>
TreeNode<T> *TreeNode<T>::Remove(int nodeKey) {
    // Searching for the node to remove
    if (nodeKey > getKey()) {
        // The delete target is a right child of the current node
        if (right) {
            right->Remove(nodeKey);
        } else {
            return this;
        }
    } else if (nodeKey < getKey()) {
        // The delete target is a left child of the current node
        if (left) {
            left->Remove(nodeKey);
        } else {
            return this;
        }
    } else {
        // Found the node we need to delete
        // Using delete handler to remove the node from the tree
        return this->DeleteNode();
    }
    // Rebalancing tree after removal
    return Rebalance();
}

/**
 * Deletes the node from the tree, returns the new root of the node's subtree
 * after it's removal
 * @tparam T Pointer to dynamically allocated object of type T
 * @return The new root of the node's subtree after it's removal
 */
template<class T>
TreeNode<T> *TreeNode<T>::DeleteNode() {
    // Search for the next node to act as subtree root
    if (left) {
        return DeleteAndReplaceNodeWithLeftSuccessor();
    } else if (right) {
        return DeleteAndReplaceNodeWithRightSuccessor();
    } else {
        // The node we want to delete has no leafs, so it's subtree will remain empty
        // after deletion.
        this->SwapNodesParent(nullptr);
        delete this;
        return nullptr;
    }
}

/**
 * Finds the minimal node from this point downward in the tree
 * @tparam T Pointer to dynamically allocated object of type T
 * @return The minimal node
 */
template<class T>
TreeNode<T> *TreeNode<T>::findMin() {
    if (left) {
        return left->findMin();
    }
    return this;
}

/**
 * Finds the maximal node from this point downward in the tree
 * @tparam T Pointer to dynamically allocated object of type T
 * @return The maximal node
 */
template<class T>
TreeNode<T> *TreeNode<T>::findMax() {
    if (right) {
        return right->findMax();
    }
    return this;
}

/**
 * Returns the left child of the node
 * @tparam T Pointer to dynamically allocated object of type T
 * @return The left child of the node
 */
template<class T>
TreeNode<T> *TreeNode<T>::getLeft() {
    return left;
}

/**
 * Sets the left child of the node
 * @tparam T Pointer to dynamically allocated object of type T
 * @param ptr The new left child of the node
 */
template<class T>
void TreeNode<T>::setLeft(TreeNode<T> *ptr) {
    left = ptr;
}

/**
 * Returns the right child of the node
 * @tparam T Pointer to dynamically allocated object of type T
 * @return The right child of the node
 */
template<class T>
TreeNode<T> *TreeNode<T>::getRight() {
    return right;
}

/**
 * Sets the right child of the node
 * @tparam T Pointer to dynamically allocated object of type T
 * @param ptr The new right child of the node
 */
template<class T>
void TreeNode<T>::setRight(TreeNode<T> *ptr) {
    right = ptr;
}

/**
 * Returns the parent of the node
 * @tparam T Pointer to dynamically allocated object of type T
 * @return The parent of the node
 */
template<class T>
TreeNode<T> *TreeNode<T>::getParent() {
    return parent;
}

/**
 * Sets the parent of the node
 * @tparam T Pointer to dynamically allocated object of type T
 * @param ptr The new parent of the node
 */
template<class T>
void TreeNode<T>::setParent(TreeNode<T> *ptr) {
    parent = ptr;
}

template<class T>
void TreeNode<T>::removeDataPointer() {
    data = nullptr;
}

/**
 * Generic Template Class for an AVL Tree
 * Stores and organizes AVL tree nodes meant to store dynamic user data
 * @tparam T Pointer to dynamically allocated object of type T
 */
template<class T>
class Tree {
    TreeNode<T> *root;

public:
    Tree();

    TreeNode<T> *GetRoot();

    void MarkRootAsNullptr();

    void MarkRootDataAsNullptr();

    TreeNode<T> *Find(int key);

    void Insert(int key, T *data = nullptr);

    TreeNode<T> *InsertGetBack(int key, T *data);

    void Remove(int key);

    bool IsRootNull();

    ~Tree();
};

/**
 * =============================================================================
 * Tree Functions Implementation
 * =============================================================================
 */

/**
 * Creates an empty AVL Tree to store nodes with type T
 * @tparam T Pointer to dynamically allocated object of type T
 */
template<class T>
Tree<T>::Tree(): root(nullptr) {};


/**
 * Returns a pointer to the root of the tree
 * @tparam T Pointer to dynamically allocated object of type T
 * @return A pointer to the root of the tree
 */
template<class T>
TreeNode<T> *Tree<T>::GetRoot() {
    if (root) {
        return root;
    }
    return nullptr;
}

/**
 * Searches for a node by key in the tree and returns it if it exists
 * @tparam T Pointer to dynamically allocated object of type T
 * @param key The key of the node to find
 * @return A pointer to the node if it's found in the tree, nullptr otherwise
 */
template<class T>
TreeNode<T> *Tree<T>::Find(int key) {
    if (!root) {
        return nullptr;
    }

    return root->Find(key);
}

/**
 * Inserts a new node with the given key and data to the tree
 * If the key already exists in the tree, nothing will be done
 * (This also means the dynamic data sent to the function will not
 * be freed)
 * @tparam T Pointer to dynamically allocated object of type T
 * @param key The key of the new node
 * @param data The data of the new node
 */
template<class T>
void Tree<T>::Insert(int key, T *data) {
    if (!root) {
        // The tree is empty, inserting the new node as the root
        root = new TreeNode<T>(key, data);
    } else {
        root = root->Insert(key, data);
    }
}

/**
 * Insert a new node to the subtree tree and returns a pointer to the new node
 * @tparam T Pointer to dynamically allocated object of type T
 * @param key The key of the new node
 * @param data The data object of the new node
 * @param result A pointer to save a reference to the new node in
 * @return A pointer to the newely inserted ndoe
 */
template<class T>
TreeNode<T> *Tree<T>::InsertGetBack(int key, T *data) {
    if (!root) {
        // The tree is empty, inserting the new node as the root
        root = new TreeNode<T>(key, data);
        return root;
    } else {
        TreeNode<T> *result = nullptr;
        root = root->Insert(key, data, result);
        return result;
    }
}

/**
 * Removes a node with the given key from the tree
 * @tparam T Pointer to dynamically allocated object of type T
 * @param key The key of the node to remove
 */
template<class T>
void Tree<T>::Remove(int key) {
    if (root) {
        root = root->Remove(key);
    }
}

/**
 * Checks if the tree is empty
 * @tparam T Pointer to dynamically allocated object of type T
 * @return True if the root of the tree is a nullptr, False otherwiese
 */
template<class T>
bool Tree<T>::IsRootNull() {
    return (root == nullptr);
}

/**
 * Marks the root of the tree as nullptr
 * @tparam T Pointer to dynamically allocated object of type T
 */
template<class T>
void Tree<T>::MarkRootAsNullptr() {
    root = nullptr;
}

/**
 * Marks the data of the root of the tree as nullptr
 * @tparam T Pointer to dynamically allocated object of type T
 */
template<class T>
void Tree<T>::MarkRootDataAsNullptr() {
    root->removeDataPointer();
}

/**
 * Deletes all nodes stored in the tree, including the dynamic data stored in them
 * and then sets the root of the tree to nullptr
 * @tparam T Pointer to dynamically allocated object of type T
 */
template<class T>
Tree<T>::~Tree() {
    if (root) {
        root->DeleteTreeData();
        delete root;
        root = nullptr;
    }
}


#endif //WET1_TREE_H
