//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_TREENODE_H
#define WET1_TREENODE_H

#include <memory>
#include "../library1.h"
#include "../MostPlayedList/ArtistPlaysNode.h"

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

    virtual void SetHeight(int height);

    virtual StatusType AddNode(shared_ptr<TreeNode> node);

    virtual StatusType RemoveNode(int key);

    virtual shared_ptr<TreeNode> GetFather();

    virtual shared_ptr<TreeNode> GetLeft();

    virtual shared_ptr<TreeNode> GetRight();

    virtual shared_ptr<TreeNode> Find(int key);

    virtual StatusType AddNodeT(TreeNode *node);
};


#endif //WET1_TREENODE_H
