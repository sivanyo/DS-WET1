//
// Created by Mor on 30/04/2020.
//

#ifndef WET1_SONGPLAYS_H
#define WET1_SONGPLAYS_H

#include <memory>
#include "../TreeNode/TreeNode.h"

using std::shared_ptr;
using std::make_shared;

class MostPlayedListNode;

class SongPlays {
private:
    int songId;
    int numberOfPlays = 0;
    int artistId;
    shared_ptr<MostPlayedListNode> ptrToListNode;
public:
    SongPlays(int songId, int artistId, shared_ptr<MostPlayedListNode> ptrToListNode);

    int GetSongId() const;

    int GetNumberOfPlays() const;

    int GetArtistId() const;

    void IncrementNumberOfPlays();

    shared_ptr<MostPlayedListNode> GetPtrToListNode();

    void SetPtrToListNode(shared_ptr<MostPlayedListNode> listNode);
};

typedef TreeNode<SongPlays> SongPlaysNode;


#endif //WET1_SONGPLAYS_H
