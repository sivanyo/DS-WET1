//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_TREENODE_H
#define WET1_TREENODE_H

#include <memory>
#include "../library1.h"

using std::unique_ptr;
using std::weak_ptr;

class TreeNode {
protected:
    int key;
    weak_ptr<TreeNode> father;
    unique_ptr<TreeNode> left;
    unique_ptr<TreeNode> right;
public:
    explicit TreeNode(int key);

    TreeNode(int key, TreeNode *father, TreeNode *left, TreeNode *right);

    virtual int GetKey();

    virtual void SetKey(int key);

    virtual StatusType AddNode(TreeNode *node);

    virtual StatusType RemoveNode(int key);

    virtual TreeNode *GetFather();

    virtual TreeNode *GetLeft();

    virtual TreeNode *GetRight();

    virtual TreeNode *Find(int key);
};


#endif //WET1_TREENODE_H
