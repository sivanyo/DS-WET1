//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_TREENODE_H
#define WET1_TREENODE_H

#include "library1.h"

class TreeNode {
protected:
    int key;
    TreeNode* father;
    TreeNode* left;
    TreeNode* right;
public:
    explicit TreeNode(int key);
    TreeNode(int key, TreeNode* father, TreeNode* left, TreeNode* right);

    virtual int GetKey();

    virtual StatusType AddNode(TreeNode node);
    virtual StatusType RemoveNode(TreeNode node);
    virtual TreeNode GetFather();
    virtual TreeNode GetLeft();
    virtual TreeNode GetRight();
};


#endif //WET1_TREENODE_H
