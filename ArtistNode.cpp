//
// Created by Mor on 26/04/2020.
//

#include "TreeNode.h"
#include "ArtistNode.h"

ArtistNode::ArtistNode(int artistId, int numberOfSongs) : TreeNode(artistId), data(Artist(artistId, numberOfSongs)) {
}

Artist ArtistNode::GetData() {
    return this->data;
}
