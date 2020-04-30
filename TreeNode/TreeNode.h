//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_TREENODE_H
#define WET1_TREENODE_H

#include <iostream>
#include <memory>
#include "../library1.h"

using namespace std;
using std::shared_ptr;
using std::make_shared;

class TreeNode {
protected:
    int key;
    int height;
    shared_ptr<TreeNode> father;
    shared_ptr<TreeNode> left;
    shared_ptr<TreeNode> right;
public:
    explicit TreeNode(int key);

    TreeNode(int key, shared_ptr<TreeNode> father, shared_ptr<TreeNode> left, shared_ptr<TreeNode> right);

    virtual int GetKey();

    virtual void SetKey(int key);

    virtual int GetHeight();

    void SetHeight(int height);

    StatusType AddNode(const shared_ptr<TreeNode>& node);

    StatusType RemoveNode(int key);

    virtual shared_ptr<TreeNode> GetFather();

    virtual shared_ptr<TreeNode> GetLeft();

    virtual shared_ptr<TreeNode> GetRight();

    virtual shared_ptr<TreeNode> Find(int key);

    static int max (int a,int b);

    static int CalcHeight (const shared_ptr<TreeNode>& node);

    void SetFather (shared_ptr<TreeNode> newFather);

    shared_ptr<TreeNode> FindMin(shared_ptr<TreeNode> node);

    shared_ptr<TreeNode> FindMax(shared_ptr<TreeNode>node);

    int GetBalance(shared_ptr<TreeNode>node);

    shared_ptr<TreeNode> LL (shared_ptr<TreeNode>node);

    shared_ptr<TreeNode> LR (shared_ptr<TreeNode>node);

    shared_ptr<TreeNode> RR (shared_ptr<TreeNode>node);

    shared_ptr<TreeNode> RL (shared_ptr<TreeNode>node);




};


#endif //WET1_TREENODE_H
