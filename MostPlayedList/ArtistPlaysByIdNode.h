//
// Created by Mor on 27/04/2020.
//

#ifndef WET1_ARTISTPLAYSBYIDNODE_H
#define WET1_ARTISTPLAYSBYIDNODE_H


#include "../TreeNode/TreeNode.h"
#include "SongPlaysByArtistIdNode.h"

class ArtistPlaysByIdNode: public TreeNode {
private:
    int artistId;
    SongPlaysByArtistIdNode artistSongsTree;
public:
    ArtistPlaysByIdNode(int artistId, SongPlaysByArtistIdNode artistSongsTree);
};


#endif //WET1_ARTISTPLAYSBYIDNODE_H
