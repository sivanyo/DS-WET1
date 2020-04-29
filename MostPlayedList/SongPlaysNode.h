//
// Created by Mor on 27/04/2020.
//

#ifndef WET1_SONGPLAYSNODE_H
#define WET1_SONGPLAYSNODE_H


#include "../TreeNode/TreeNode.h"
#include "MostPlayedListNode.h"

class SongPlaysNode : public TreeNode {
private:
    int songId;
    int numberOfPlays;
    int artistId;
    shared_ptr<MostPlayedListNode> ptrToListNode;
public:
    SongPlaysNode(int songId, int artistId, shared_ptr<MostPlayedListNode> ptrToList);

    int GetSongId() const;

    int GetNumberOfPlays() const;

    int GetArtistId() const;

    void IncrementNumberOfPlays();

    shared_ptr<MostPlayedListNode> GetPtrToListNode();

    void SetPtrToListNode(shared_ptr<MostPlayedListNode> listNode);
};


#endif //WET1_SONGPLAYSNODE_H
