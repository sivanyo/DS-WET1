//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_TREENODE_H
#define WET1_TREENODE_H

#include <memory>
#include "../library1.h"

using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;

template <class T>
class TreeNode : public std::enable_shared_from_this<TreeNode<T>> {
protected:
    int key;
    int height = 0;
    T data;
    weak_ptr<TreeNode<T>> father;
    shared_ptr<TreeNode<T>> left;
    shared_ptr<TreeNode<T>> right;
public:
    TreeNode(int key, T data);

    TreeNode(int key, T data, shared_ptr<TreeNode<T>> father, shared_ptr<TreeNode<T>> left, shared_ptr<TreeNode<T>> right);

    int GetKey();

    void SetKey(int key);

    int GetHeight();

    void SetHeight(int height);

    virtual T& GetData();

    virtual void SetData(T data);

    StatusType AddNode(shared_ptr<TreeNode<T>> node);

    StatusType RemoveNode(int key);

    virtual shared_ptr<TreeNode<T>> FindRoot();

    virtual shared_ptr<TreeNode<T>> GetFather();

    virtual shared_ptr<TreeNode<T>> GetLeft();

    virtual shared_ptr<TreeNode<T>> GetRight();

    virtual shared_ptr<TreeNode<T>> Find(int key);

    static int CalcHeight (const shared_ptr<TreeNode<T>>& node);

    void SetFather (shared_ptr<TreeNode<T>> newFather);

    bool IsOnlyRoot();

    shared_ptr<TreeNode<T>> FindMin();

    shared_ptr<TreeNode<T>> FindMax();

    static shared_ptr<TreeNode> LeftRotate (const shared_ptr<TreeNode>&node);

    static shared_ptr<TreeNode> RightRotate (const shared_ptr<TreeNode>&node);

    int GetBalance(const shared_ptr<TreeNode> node);

    shared_ptr<TreeNode<T>> GetNextNode(const shared_ptr<TreeNode<T>> &node);

    void DeleteTree (shared_ptr<TreeNode<T>> root);
    void DeleteTree ();

};

#include "TreeNodeImp.h"
#endif //WET1_TREENODE_H
