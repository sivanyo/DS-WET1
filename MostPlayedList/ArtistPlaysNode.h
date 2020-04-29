//
// Created by Mor on 27/04/2020.
//

#ifndef WET1_ARTISTPLAYSNODE_H
#define WET1_ARTISTPLAYSNODE_H

#include <memory>
#include "SongPlaysNode.h"

using std::shared_ptr;
using std::make_shared;

class ArtistPlaysNode : public TreeNode {
private:
    int artistId;
    shared_ptr<SongPlaysNode> SongPlaysTree;
    shared_ptr<MostPlayedListNode> ptrToListNode;
public:
    ArtistPlaysNode(int artistId);
    ArtistPlaysNode(int artistId, shared_ptr<SongPlaysNode> ptrToSongPlaysTree, shared_ptr<MostPlayedListNode> ptrToListNode);
    int GetArtistId();


};


#endif //WET1_ARTISTPLAYSNODE_H
