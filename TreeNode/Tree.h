//
// Created by Mor on 03/05/2020.
//

#ifndef WET1_TREE_H
#define WET1_TREE_H

#include <memory>

const int LEFT_HEAVY = 1;
const int RIGHT_HEAVY = 1;
const int BALANCED = 0;

using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;

// TODO: sivan remembers in binary(carry), to change the names of these template vars

template<typename K, class V>
class Node {
public:
    K key;
    V value;
    weak_ptr<Node<K, V>> parent;
    shared_ptr<Node<K, V>> left;
    shared_ptr<Node<K, V>> right;
    int balanceFactor;

    // Create a new node with a given key and value, under given parent node.
    Node(K key, V value, shared_ptr<Node<K, V>> parent) : key(key), value(value), parent(parent),
                                                          balanceFactor(0) {}

    // returns true if the node is the left child of its parent.
    bool IsLeftChild() const;

    // returns true if the node is the right child of its parent.
    bool IsRightChild() const;

    // Get the sibling node of a parent or nullptr if there is none.
    shared_ptr<Node<K, V>> GetSibling() const;

    // Assuming tree is AVL and both children have correct balance factors, fix the balance.
    void CorrectTreeBalance();

    friend void SetLeftChild(shared_ptr<Node<K, V>> parent_node, shared_ptr<Node<K, V>> child) {
        parent_node->left_child = child;
        if (child) { child->parent = parent_node; }
    }

    friend void SetRightChild(shared_ptr<Node<K, V>> parent_node, shared_ptr<Node<K, V>> child) {
        parent_node->right_child = child;
        if (child) { child->parent = parent_node; }
    }

    // Find a node with the given key; a helper for insertion, retrieval and removal.
    // Returns:
    //   1. If the tree is empty --> null pointer.
    //   2. If the key exists --> A pointer to the node with that key.
    //   2. If the key doesn't exist, but the tree isn't empty --> a pointer to its parent.
    static shared_ptr<Node<K, V>> _node_search(K key, shared_ptr<Node<K,V>> root);


    // After insertion retrace from this node back to the root, check for imbalance and correct it.
    static void _retrace_insertion(shared_ptr<Node<K, V>> inserted_node);

    class Tree {
    protected:
        // A pointer to the root `node` of the tree. If this is null, then the tree is empty.
        shared_ptr<Node<K, V>> root;
    public:

        void insert(const K &key, const V &value);

        /**
         * Adds a new key-value pair to the tree and returns a pointer to it
         * @param key The key
         * @param value The value associated with the key
         * @return A shared_ptr to the node in the tree
         */
        shared_ptr<Node<K, V>> insertGetBack(const K &key, const V &value);

        /**
         * Find a node with the given key and return a pointer to it
         * @param key The key of the node to get
         * @return A shared_ptr to the node in the tree
         */
        shared_ptr<Node<K, V>> getNode(const K &key);

        // Find the value associated with a given key. Returns an `optional` struct since the key isn't
        // guaranteed to be present in the tree.
        V get(const K &key) const;

        // Check if a node exists in the tree with a given value. Returns true if it does, false
        // otherwise.
        bool exists(const K &key) const;

        // Remove node from the tree with given key. Doesn't matter if the node isn't there.
        void remove(const K &key);

        // After deletion retrace from this node back to the root, check for imbalance and correct it.
        // The balance_factor_change argument indicates which side the child of the subtree root had
        // a child removed.
        void _retrace_deletion(shared_ptr<Node<K, V>> subtree_root, int balance_factor_change);

        // Perform a left rotation to rebablance a subtree rooted at old_subtree_root, returning
        // a pointer to the new root of the subtree.
        shared_ptr<Node<K, V>> _left_rotate(shared_ptr<Node<K, V>> old_subtree_root);

        // Perform a right rotation to rebablance a subtree rooted at old_subtree_root, returning
        // a pointer to the new root of the subtree.
        shared_ptr<Node<K, V>> _right_rotate(shared_ptr<Node<K, V>> old_subtree_root);

        // Perform a left-right rotation to rebablance a subtree rooted at old_subtree_root, returning
        // a pointer to the new root of the subtree.
        shared_ptr<Node<K, V>> _left_right_rotate(shared_ptr<Node<K, V>> old_subtree_root);

        // Perform a right-left rotation to rebablance a subtree rooted at old_subtree_root, returning
        // a pointer to the new root of the subtree.
        shared_ptr<Node<K, V>> _right_left_rotate(shared_ptr<Node<K, V>> old_subtree_root);
    };

};

/**
 * ===============================================================================================
 * Node internal methods
 * ===============================================================================================
 */

// returns true if the node is the left child of its parent.
template<typename K, typename V>
bool Node<K, V>::IsLeftChild() const {
    // Looking parent weak_ptr to enable safe usage
    shared_ptr<Node<K, V>> parent_ptr = parent.lock();
    if (parent_ptr) {
        if (parent_ptr->left_child) {
            return key == parent_ptr->left_child->key;
        }
    }
    return false;
}

// returns true if the node is the right child of its parent.
template<typename K, typename V>
bool Node<K, V>::IsRightChild() const {
    shared_ptr<Node<K, V>> parent_ptr = parent.lock();
    if (parent_ptr) {
        if (parent_ptr->right_child) {
            return key == parent_ptr->right_child->key;
        }
    }
    return false;
}

// get the sibling node of a parent or nullptr if there is none.
template<typename K, typename V>
shared_ptr<Node<K, V>> Node<K, V>::GetSibling() const {
    if (IsLeftChild())
        return parent.lock()->left_child;
    else
        return parent.lock()->right_child;
}

// Assuming tree is AVL and both children have correct balance factors...
template<typename K, typename V>
void Node<K, V>::CorrectTreeBalance() {
    if (left && right) {
        if (abs(left->balance_factor) == abs(right->balance_factor))
            balanceFactor = 0;
        else if (left->balance_factor)
            balanceFactor = LEFT_HEAVY;
        else
            balanceFactor = RIGHT_HEAVY;
    } else if (left)
        balanceFactor = LEFT_HEAVY;
    else
        balanceFactor = RIGHT_HEAVY;
}

// Inserts a node with the given key and value
template<typename K, typename V>
void Node<K, V>::Tree::insert(const K &key, const V &value) {
    if (!root) {
        // Tree is empty, insert node as new root
        root = make_shared<Node<K, V>>(key, value, nullptr);
    } else {
        shared_ptr<Node<K, V>> target = _node_search(key, root);
        if (target->key == key) {
            // The key already exists, we won't insert again
        } else if (target->key > key) {
            // The new node is a left child of the current node
            target->left = make_shared<Node<K, V>>(key, value, target);
            _retrace_insertion(target->left);
        } else {
            // The new node is a right child of the current node
            target->right = make_shared<Node<K, V>>(key, value, target);
            _retrace_insertion(target->right);
        }
    }
}

// Insert a node with the given key and value and returns a shared_ptr to the new node
template<typename K, typename V>
shared_ptr<Node<K, V>> Node<K, V>::Tree::insertGetBack(const K &key, const V &value) {
    if (!root) {
        // Tree is empty, insert node as new root
        root = make_shared<Node<K, V>>(key, value, nullptr);
        return root;
    } else {
        shared_ptr<Node<K, V>> target = _node_search(key, root);
        if (target->key == key) {
            // The key already exists, we won't insert again
        } else if (target->key > key) {
            // The new node is a left child of the current node
            target->left = make_shared<Node<K, V>>(key, value, target);
            _retrace_insertion(target->left);
            return target->left;
        } else {
            // The new node is a right child of the current node
            target->right = make_shared<Node<K, V>>(key, value, target);
            _retrace_insertion(target->right);
            return target->right;
        }
    }
}

// Get the value of a node with a given key, the function will return either
// the node's value itself, the value of it's logical parent (if the node doesn't exist)
// or nullptr if the tree is empty
template<typename K, typename V>
V Node<K, V>::Tree::get(const K &key) const {
    shared_ptr<Node<K, V>> found_node = _node_search(key, root);
    if (found_node && (key == found_node->key))
        return V(found_node->value);
    return;
}

// Get a node with a given key, the function will return either
// the node itself, the node of it's logical parent (if the node doesn't exist)
// or nullptr if the tree is empty
template<typename K, typename V>
shared_ptr<Node<K, V>> Node<K, V>::Tree::getNode(const K &key) {
    shared_ptr<Node<K, V>> found_node = _node_search(key, root);
    if (found_node && (key == found_node->key))
        return found_node;
    return nullptr;
}

// Check if a key exists in the tree, returns true if a node with the key
// exists and false otherwise.
template<typename K, typename V>
bool Node<K, V>::Tree::exists(const K &key) const {
    shared_ptr<Node<K, V>> found_node = _node_search(key, root);
    return found_node && (key == found_node->key);
}

// Remove a node with given key from the tree
template<typename K, typename V>
void Node<K, V>::Tree::remove(const K &key) {
    shared_ptr<Node<K, V>> target = _node_search(key, root);
    // does the target node exist?
    if (!(target && (key == target->key)))
        return;

    // checking if the node has more than one child
    if (target->left_child || target->right_child) {
        // checking if the node has 2 children
        if (target->left_child && target->right_child) {
            // find in-order successor (node with smallest key that is > than this key)
            shared_ptr<Node<K, V>> successor = target->right_child;
            shared_ptr<Node<K, V>> successor_parent;
            while (successor->left_child)
                successor = successor->left_child;
            successor_parent = successor->parent.lock();

            // successor has a right child? (if it had left-child, it wouldn't be in-order successor!)
            if (successor->right_child) {
                // We need to reseat this child where "successor" lived.
                if (successor->is_left_child())
                    set_left_child(successor_parent, successor->right_child);
                else // successor is a right child
                    set_right_child(successor_parent, successor->right_child);
            } else  // Successor had no children, can just be removed.
            {
                if (successor->is_left_child())
                    successor_parent->left_child = nullptr;
                else // successor is a right child
                    successor_parent->right_child = nullptr;
            }
            // We are moving this node's key and value to our deleted node lived, and deleting this.
            target->key = successor->key;
            target->value = successor->value;
            if (successor->is_left_child()) {
                _retrace_deletion(successor_parent, -LEFT_HEAVY);
            } else {
                _retrace_deletion(successor_parent, -RIGHT_HEAVY);
            }
        }
            // checking if the node has one child
        else {
            // get pointer to the node that would be orphaned
            shared_ptr<Node<K, V>> orphan = (target->left_child) ? target->left_child : target->right_child;
            // If the root is being deleted, this orphan must become the new root
            if (target == root)
                root = orphan;
                // otherwise, assign it to the side of parent that our target node lived
            else if (target->is_left_child()) {
                set_left_child(target->parent.lock(), orphan);
            } else
                set_right_child(target->parent.lock(), orphan);
        }
    }
        // Removed node has 0 children
    else {
        if (target == root)  // parent == null in this case
        {
            root = nullptr;     // we remove the root, leaving an empty tree, no balancing required
        } else if (target->is_left_child()) {
            // locking parent ptr to enable safe usage of weak_ptr
            target->parent.lock()->left_child = nullptr;
            _retrace_deletion(target->parent.lock(), -LEFT_HEAVY);
        } else {
            // locking parent ptr to enable safe usage of weak_ptr
            target->parent.lock()->right_child = nullptr;
            _retrace_deletion(target->parent.lock(), -RIGHT_HEAVY);
        }
    }
}

// This function receives a key and searches for the node with the given key,
// The function will return the node with the key if it exists, or a pointer
// To it's parent if it doesn't
template<typename K, typename V>
shared_ptr<Node<K, V>> Node<K, V>::_node_search(K key, shared_ptr<Node<K,V>> root) {
    // Base case, we have an empty tree.
    if (!root)
        return nullptr;
    // Iterative search. We follow branch directions based on comparing the keys.
    shared_ptr<Node<K, V>> current = root;
    for (;;) {
        if (key < current->key)
            if (current->left_child)
                current = current->left_child;
            else
                return current;
        else if (key > current->key)
            if (current->right_child)
                current = current->right_child;
            else
                return current;
        else // (key == current->key)
            return current;
    }
}

// Retrace after a node is inserted in order to check tree is still AVL and, if not, rebalance it.
template<typename K, typename V>
void Node<K, V>::_retrace_insertion(shared_ptr<Node<K, V>> inserted_node) {
    shared_ptr<Node<K, V>> current;
    shared_ptr<Node<K, V>> parent;
    for (current = inserted_node; current->parent.lock() != nullptr; current = parent) {
        parent = current->parent.lock();
        if (current->is_left_child()) {
            if (parent->balance_factor == LEFT_HEAVY) {
                // tree is unbalanced, left too heavy
                if (current->balance_factor == RIGHT_HEAVY) {
                    // left child in right subtree -> right-left double rotation
                    _left_right_rotate(parent);
                    return;
                } else {
                    // (parent->is_right_child() || parent == root) necessarily.
                    // left child in left subtree -> single right rotation
                    _right_rotate(parent);
                    return;
                }
            } else {
                parent->balance_factor += LEFT_HEAVY;
                if (parent->balance_factor == BALANCED) {
                    return;
                } else
                    continue;
            }
        } else {
            // (current->is_right_child()) necessarily, we exited loop if there was no parent, so it can't be root.
            if (parent->balance_factor == RIGHT_HEAVY) {
                //tree is unbalanced, right too heavy
                if (current->balance_factor == LEFT_HEAVY) {
                    // right child in left subtree -> left-right double rotation
                    _right_left_rotate(parent);
                    return;
                } else {
                    // (parent->is_right_child() || parent == root) necessarily.
                    // right child in right subtree -> single left rotation
                    _left_rotate(parent);
                    return;
                }
            } else {
                parent->balance_factor += RIGHT_HEAVY;
                if (parent->balance_factor == BALANCED) {
                    return;
                } else
                    continue;
            }
        }
    }
}

// Retrace after a node is deleted in order to check tree is still AVL and, if not, rebalance it.
template<typename K, typename V>
void Node<K, V>::Tree::_retrace_deletion(shared_ptr<Node<K, V>> subtree_root, int balance_factor_change) {
    shared_ptr<Node<K, V>> current = subtree_root;
    shared_ptr<Node<K, V>> mParent;

    if (current->balance_factor == BALANCED) {
        current->balance_factor += balance_factor_change;
        return;
    } else if ((current->balance_factor + balance_factor_change) != BALANCED) {
        if (balance_factor_change == LEFT_HEAVY) {
            if (subtree_root->left_child->balance_factor == LEFT_HEAVY) {
                _right_rotate(subtree_root);
            } else {
                _left_right_rotate(subtree_root);
            }
        } else {
            // RIGHT_HEAVY
            if (subtree_root->right_child->balance_factor == RIGHT_HEAVY) {
                _left_rotate(subtree_root);
            } else {
                _right_left_rotate(subtree_root);
            }
        }
        return;
    } else {
        // Subtree should be balanced...
    }

    for (current = subtree_root; current->parent.lock() != nullptr; current = mParent) {
        mParent = current->parent.lock();
        if (current->is_left_child()) {
            if (mParent->balance_factor == RIGHT_HEAVY) {
                if (current->balance_factor == RIGHT_HEAVY) {
                    // left rotate
                    _left_rotate(mParent);
                    return;
                } else {
                    // right-left rotate
                    _right_left_rotate(mParent);
                    return;
                }
            } else {
                mParent->balance_factor -= LEFT_HEAVY;
                if (mParent->balance_factor == BALANCED) {
                    return;
                } else
                    continue;
            }
        } else {
            // (current is a right child necessarily, we exited loop if there was no parent, so it can't be root.
            if (mParent->balance_factor == LEFT_HEAVY) {
                if (current->balance_factor == LEFT_HEAVY) {

                    _right_rotate(mParent);
                    return;
                } else {
                    _left_right_rotate(mParent);
                    return;
                }
            } else {
                mParent->balance_factor -= RIGHT_HEAVY;
                if (mParent->balance_factor == BALANCED) {
                    return;
                } else
                    continue;
            }
        }
    }
}

// Perform left rotation around given node.
template<typename K, typename V>
shared_ptr<Node<K, V>>
Node<K, V>::Tree::_left_rotate(shared_ptr<Node<K, V>> old_subtree_root) {
    shared_ptr<Node<K, V>> new_subtree_root = old_subtree_root->right_child;
    shared_ptr<Node<K, V>> grandparent = old_subtree_root->parent.lock();
    shared_ptr<Node<K, V>> orphan = new_subtree_root->left_child;

    if (old_subtree_root->is_left_child())
        set_left_child(grandparent, new_subtree_root);
    else if (old_subtree_root->is_right_child())
        set_right_child(grandparent, new_subtree_root);
    else {
        // old_subtree_root is whole tree root.
        root = new_subtree_root;
        new_subtree_root->parent.reset();
    }
    set_left_child(new_subtree_root, old_subtree_root);
    set_right_child(old_subtree_root, orphan);

    if (old_subtree_root->balance_factor == BALANCED) {
        new_subtree_root->balance_factor = RIGHT_HEAVY;
        old_subtree_root->balance_factor = LEFT_HEAVY;
    } else {
        new_subtree_root->balance_factor = BALANCED;
        old_subtree_root->balance_factor = BALANCED;
    }
    return new_subtree_root;
}

// Perform right rotation around given node.
template<typename K, typename V>
shared_ptr<Node<K, V>>
Node<K, V>::Tree::_right_rotate(shared_ptr<Node<K, V>> old_subtree_root) {
    shared_ptr<Node<K, V>> new_subtree_root = old_subtree_root->left_child;
    shared_ptr<Node<K, V>> grandparent = old_subtree_root->parent.lock();
    shared_ptr<Node<K, V>> orphan = new_subtree_root->right_child;  // may be nullptr


    if (old_subtree_root->is_left_child())
        set_left_child(grandparent, new_subtree_root);
    else if (old_subtree_root->is_right_child())
        set_right_child(grandparent, new_subtree_root);
    else {
        // old_subtree_root is whole tree root.
        root = new_subtree_root;
        new_subtree_root->parent.reset();
    }
    set_right_child(new_subtree_root, old_subtree_root);
    set_left_child(old_subtree_root, orphan);

    if (old_subtree_root->balance_factor == BALANCED) {
        new_subtree_root->balance_factor = LEFT_HEAVY;
        old_subtree_root->balance_factor = RIGHT_HEAVY;
    } else {
        new_subtree_root->balance_factor = BALANCED;
        old_subtree_root->balance_factor = BALANCED;
    }
    return new_subtree_root;
}

// Perform left-right rotation around a given node.
template<typename K, typename V>
shared_ptr<Node<K, V>>
Node<K, V>::Tree::_left_right_rotate(shared_ptr<Node<K, V>> old_subtree_root) {
    _left_rotate(old_subtree_root->left_child);
    return _right_rotate(old_subtree_root);
}

// Perform right-left rotation around a given node.
template<typename K, typename V>
shared_ptr<Node<K, V>>
Node<K, V>::Tree::_right_left_rotate(shared_ptr<Node<K, V>> old_subtree_root) {
    _right_rotate(old_subtree_root->right_child);
    return _left_rotate(old_subtree_root);
}

#endif //WET1_TREE_H
