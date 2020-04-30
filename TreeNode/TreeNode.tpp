//
// Created by Mor on 26/04/2020.
//

#include <memory>

using std::shared_ptr;
using std::make_shared;

template<class T>
TreeNode<T>::TreeNode(int key, T data) : key(key), data(data), father(nullptr), left(nullptr), right(nullptr) {
}

template<class T>
TreeNode<T>::TreeNode(int key, T data, shared_ptr<TreeNode<T>> father, shared_ptr<TreeNode<T>> left, shared_ptr<TreeNode<T>> right):
        key(key),
        data(data),
        left(left),
        right(right),
        father(father) {
}

template<class T>
int TreeNode<T>::GetKey() {
    return this->key;
}

template<class T>
void TreeNode<T>::SetKey(int key) {
    this->key = key;
}

template<class T>
int TreeNode<T>::GetHeight() {
    return this->height;
}

template<class T>
void TreeNode<T>::SetHeight(int height) {
    this->height = height;
}

template<class T>
T TreeNode<T>::GetData() {
    return this->data;
}

template<class T>
void TreeNode<T>::SetData(T data) {
    this->data = data;
}

template<class T>
shared_ptr<TreeNode<T>> TreeNode<T>::GetFather() {
    return this->father;
}

template<class T>
shared_ptr<TreeNode<T>> TreeNode<T>::GetLeft() {
    return this->left;
}

template<class T>
shared_ptr<TreeNode<T>> TreeNode<T>::GetRight() {
    return this->right;
}

template<class T>
StatusType TreeNode<T>::AddNode(int test) {
    return SUCCESS;
}

template<class T>
StatusType TreeNode<T>::AddNode(const shared_ptr<TreeNode<T>> &node) {
    //adding the node
    if (this->GetRight() == nullptr && this->GetLeft() == nullptr) {
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
        else {
            return FAILURE;
        }
        node->SetHeight(1); //always added as a leaf

        //TODO: add rotations

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

template<class T>
StatusType TreeNode<T>::RemoveNode(int key) {
    //there isn't any node with a matching key in the tree
    if (this->GetRight() == nullptr && this->GetLeft() == nullptr && this->GetKey() != key) {
        return FAILURE;
    }
    //searching for element
    if (this->GetKey() > key) {
        return this->GetLeft()->RemoveNode(key);
    } else if (this->GetKey() < key) {
        return this->GetRight()->RemoveNode(key);
    }
        //found a matching key, should remove this node
    else {
        //with one child or zero
        if (this->GetRight() == nullptr || this->GetLeft() == nullptr) {
            shared_ptr<TreeNode<T>>(temp) = (this->GetRight() ? this->GetLeft() : this->GetRight());
            //no child case
            if (temp == nullptr) {
                temp = shared_ptr<TreeNode>(this);
                shared_ptr<TreeNode<T>>(this).reset();
            }
                // one child case
            else {
                shared_ptr<TreeNode<T>>(this) = temp; //copy the contents of the non empty child
                shared_ptr<TreeNode<T>>(temp).reset();
            }

        }
            //with two children case
        else {
            shared_ptr<TreeNode<T>>(temp) = FindMin(shared_ptr<TreeNode<T>>(this));
            this->SetKey(temp->GetKey()); //Copy the inorder successor's data to this node
            this->GetRight()->RemoveNode(temp->GetKey()); //Delete the inorder successor
        }

        //update the height of the current node
        this->SetHeight(1 + max(this->GetLeft()->height, this->GetRight()->height));

        //get the BF of this node
        int balance = GetBalance(shared_ptr<TreeNode<T>>(this));


    }
}

template<class T>
shared_ptr<TreeNode<T>> TreeNode<T>::Find(int key) {
    if (this->key == key) {
        return shared_ptr<TreeNode<T>>(this);
    }
    shared_ptr<TreeNode<T>> result = this->left->Find(key);
    if (result != nullptr) {
        return result;
    }
    result = this->right->Find(key);
    if (result != nullptr) {
        return result;
    }
    return nullptr;
}

template<class T>
int TreeNode<T>::CalcHeight(const shared_ptr<TreeNode<T>> &node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}

template<class T>
void TreeNode<T>::SetFather(shared_ptr<TreeNode<T>> newFather) {
    this->father = newFather;
}

template<class T>
int TreeNode<T>::GetBalance(shared_ptr<TreeNode<T>> node) {
    if (node == nullptr)
        return 0;
    return height(node->GetLeft()) -
           height(node->GetRight());
}

template<class T>
shared_ptr<TreeNode<T>> TreeNode<T>::FindMax(shared_ptr<TreeNode<T>> node) {
    if (node == nullptr)
        return nullptr;
    else if (node->GetLeft() == nullptr)
        return node;
    else
        return FindMin(node->GetLeft());
}

template<class T>
shared_ptr<TreeNode<T>> TreeNode<T>::FindMin(shared_ptr<TreeNode<T>> node) {
    if (node == nullptr)
        return nullptr;
    else if (node->GetRight() == nullptr)
        return node;
    else
        return FindMax(node->GetRight());
}

template<class T>
shared_ptr<TreeNode<T>> TreeNode<T>::LL(shared_ptr<TreeNode<T>> node) {
    return shared_ptr<TreeNode<T>>();
}

template<class T>
shared_ptr<TreeNode<T>> TreeNode<T>::LR(shared_ptr<TreeNode<T>> node) {
    return shared_ptr<TreeNode<T>>();
}

template<class T>
shared_ptr<TreeNode<T>> TreeNode<T>::RR(shared_ptr<TreeNode<T>> node) {
    shared_ptr<TreeNode<T>> nodeLeft = node->GetLeft();
    shared_ptr<TreeNode<T>> nodeRight = node->GetRight();

    //perform rotation
    nodeLeft->right = node;
    node->left = nodeRight;

    //update heights
    node->SetHeight(max(node->left->GetHeight(), node->right->GetHeight()) + 1);
    nodeLeft->SetHeight(max(node->left->GetHeight(), node->right->GetHeight()) + 1);
    //return new root
    return nodeLeft;
}

template<class T>
shared_ptr<TreeNode<T>> TreeNode<T>::RL(shared_ptr<TreeNode<T>> node) {
    return shared_ptr<TreeNode<T>>();
}

