//
// Created by Mor on 26/04/2020.
//

#ifndef WET1_ARTISTNODE_H
#define WET1_ARTISTNODE_H


#include "TreeNode.h"
#include "Artist.h"

class ArtistNode : public TreeNode {
private:
    Artist data;
public:
    ArtistNode(int artistId, int numberOfSongs);
    Artist GetData();
};


#endif //WET1_ARTISTNODE_H
