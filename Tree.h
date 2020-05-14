//
// Created by sivan on 03/05/2020.
//

#ifndef WET1_TREE_H
#define WET1_TREE_H

#include <iostream>
#include <algorithm>
#include "library1.h"
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
 * delete node and it release its data
 * does not delete its parent or sons!
 * @tparam T
 */
template<class T>
TreeNode<T>::~TreeNode() {
    if (data != nullptr) {
        delete data;
        data = nullptr;
    }
}

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
 * @tparam T
 * @return ptr to left son
 */
template<class T>
TreeNode<T> *TreeNode<T>::getLeft() {
    return this->left;
}

/**
 * @tparam T
 * @return ptr to right son
 */
template<class T>
TreeNode<T> *TreeNode<T>::getRight() {
    return this->right;
}

/**
 * @tparam T
 * @return ptr to node's parent
 */
template<class T>
TreeNode<T> *TreeNode<T>::getParent() {
    return parent;
}

/**
 * @tparam T
 * @param keyFind
 * @return a node given its key (if not found return nullptr)
 */
template<class T>
TreeNode<T> *TreeNode<T>::Find(int keyFind) {
    if (keyFind == key) {
        return this;
    } else if (keyFind < key) {
        if (left != nullptr) {
            return left->Find(keyFind);
        } else {
            return nullptr;
        }
    } else {
        if (right != nullptr) {
            return right->Find(keyFind);
        } else {
            return nullptr;
        }
    }
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
 * Find if keyRemove is one of nodes key and Remove it from struct
 * @tparam T
 * @param keyRemove
 * @return update root of sub-node-struct
 */
template<class T>
TreeNode<T> *TreeNode<T>::Remove(int keyRemove) {
    if (keyRemove < key) { //if key is lower than root, Find left subtree
        if (left != nullptr) {
            left->Remove(keyRemove);
        } else {
            return this;
        }
    } else if (keyRemove > key) { //if key is bigger than root, Find right subtree
        if (right != nullptr) {
            right->Remove(keyRemove);
        } else {
            return this;
        }
    } else { //key found, current node holds key
        return this->DeleteNode(keyRemove); // calls a function that actually delete current node
    }
    return Rebalance();
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
 *
 * @tparam T
 * @return min by key node in struct
 */
template<class T>
TreeNode<T> *TreeNode<T>::findMin() {
    if (left != nullptr) {
        return left->findMin();
    }
    return this;
}

/**
 *
 * @tparam T
 * @return max by key node in struct
 */
template<class T>
TreeNode<T> *TreeNode<T>::findMax() {
    if (right != nullptr) {
        return right->findMax();
    }
    return this;
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

template<class T>
void TreeNode<T>::setLeft(TreeNode<T> *ptr) {
    left = ptr;
}

template<class T>
void TreeNode<T>::setRight(TreeNode<T> *ptr) {
    right = ptr;
}

template<class T>
void TreeNode<T>::setParent(TreeNode<T> *ptr) {
    parent = ptr;
}

/**
 * This is a generic template for an AVL Tree - the nodes of a tree can have unique data stored in them.
 * For example, a node may hold another AVL Tree inside it
 * in this implementation, the tree "take control" on its data in the meaning it become the charge of its release/delete
*/
template<class T>
class Tree {
    TreeNode<T> *root;
    TreeNode<T> *min_node; // lowest by key data in tree

public:
    Tree();

    ~Tree();

    void Insert(int key, T *data = nullptr);

    TreeNode<T> *InsertGetBack(int key, T *data);

    void Remove(int key);

    bool IsRootNull();

    void MarkRootAsNullptr();

    TreeNode<T> *GetRoot();

    TreeNode<T> *Find(int key);

    TreeNode<T> *getMinNode();

    int mapSucc(int *keys, int size);

};

/**
 * Initialize an empty AVL tree
 */
template<class T>
Tree<T>::Tree(): root(nullptr), min_node(nullptr) {};


/**
 * delete tree and release all its data
 */
template<class T>
Tree<T>::~Tree() {
    if (root != nullptr) {
        root->DeleteTreeData();
        delete root;
        root = nullptr;
    }
}

/**
 * Insert a single data represent by key to the tree
 * if key already shows in tree - nothing will be done
 * @param key the key of the data (node)
 * @param data
 */
template<class T>
void Tree<T>::Insert(int key, T *data) {
    if (root == nullptr) { // in case the tree is empty
        root = new TreeNode<T>(key, data);
        min_node = root;
    } else {
        root = root->Insert(key, data);

        if (!min_node || key < min_node->getKey()) { // in case we Insert new min by key data
            this->min_node = root->findMin();
        }
    }
}

template<class T>
TreeNode<T> *Tree<T>::InsertGetBack(int key, T *data) {
    if (root == nullptr) { // in case the tree is empty
        root = new TreeNode<T>(key, data);
        min_node = root;
        return root;
    } else {
        TreeNode<T> *result = nullptr;
        root = root->Insert(key, data, result);

        if (!min_node || key < min_node->getKey()) { // in case we Insert new min by key data
            this->min_node = root->findMin();
        }
        return result;
    }
}

/**
 * Remove the data (node) with the key value from the tree
 * @param key
 */
template<class T>
void Tree<T>::Remove(int key) {
    bool flag = min_node != nullptr && min_node->getKey() == key;
    if (root != nullptr) {
        root = root->Remove(key);
        if (flag) {
            if (root != nullptr) {
                min_node = root->findMin();
            } else {
                min_node = nullptr;
            }
        }
    }
}

/**
 * @param key
 * @return Returns a node given its key
 * return nullptr if not found
 */
template<class T>
TreeNode<T> *Tree<T>::Find(int key) {
    if (root == nullptr) {
        return nullptr;
    }

    return root->Find(key);
}

/**
 * @return true if tree has no data, false otherwise
 */
template<class T>
bool Tree<T>::IsRootNull() {
    return (root == nullptr);
}

/**
 * @return min by key node in the tree
 */
template<class T>
TreeNode<T> *Tree<T>::getMinNode() {
    return min_node;
}

/**
 * scan the tree by "successor in-order" method
 * @tparam T
 * @param keys - arr. assign the  #size lowest keys in the tree into this arr
 * @param size - num of data to copy into keys[]
 * @return the number of keys that were assign to keys[]
 */
template<class T>
int Tree<T>::mapSucc(int *keys, int size) {
    if (size <= 0 || keys == nullptr || min_node == nullptr) {
        return 0;
    }

    return min_node->mapSucc(keys, size);
}

template<class T>
TreeNode<T> *Tree<T>::GetRoot() {
    return root;
}

/**
 * Marks the root of the tree as nullptr
 * @tparam T Pointer to dynamically allocated object of type T
 */
template<class T>
void Tree<T>::MarkRootAsNullptr() {
    root = nullptr;
}

#endif //WET1_TREE_H
